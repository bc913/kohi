#ifndef KOHI_1700444740_VULKAN_TYPES_INL
#define KOHI_1700444740_VULKAN_TYPES_INL
// This file contains VULKAN specific types

#include "defines.h"
#include "core/asserts.h"

// Checks the given expression's return value against VK_SUCCESS.
#define VK_CHECK(expr)               \
    {                                \
        KASSERT(expr == VK_SUCCESS); \
    }

#include <vulkan/vulkan.h>

// Vulkan requires surface to draw onto
// The surface will be obtained from the platform's windowing system.
typedef struct vulkan_swapchain_support_info {
    VkSurfaceCapabilitiesKHR capabilities;
    u32 format_count;  // image formats
    VkSurfaceFormatKHR* formats;
    u32 present_mode_count;
    VkPresentModeKHR* present_modes;
} vulkan_swapchain_support_info;

typedef struct vulkan_device {
    VkPhysicalDevice physical_device;
    VkDevice logical_device;
    vulkan_swapchain_support_info swapchain_support;
    i32 graphics_queue_index;
    i32 present_queue_index;
    i32 transfer_queue_index;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkQueue transfer_queue;

    VkCommandPool graphics_command_pool;

    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memory;

    VkFormat depth_format;
} vulkan_device;

typedef struct vulkan_image {
    VkImage handle;
    // Memory allocated by the image
    VkDeviceMemory memory;
    VkImageView view;
    u32 width;
    u32 height;
} vulkan_image;

typedef enum vulkan_render_pass_state {
    // renderpass is ready to begin
    READY,
    //
    RECORDING,
    // render pass running
    IN_RENDER_PASS,
    //
    RECORDING_ENDED,
    // render pass is submitted for execution
    SUBMITTED,
    NOT_ALLOCATED
} vulkan_render_pass_state;

typedef struct vulkan_renderpass {
    VkRenderPass handle;
    // render area
    // an area of the image to render to
    f32 x, y, w, h;
    // Clear colors
    f32 r, g, b, a;

    f32 depth;
    u32 stencil;

    vulkan_render_pass_state state;
} vulkan_renderpass;

typedef struct vulkan_framebuffer {
    VkFramebuffer handle;
    u32 attachment_count;
    VkImageView* attachments;
    vulkan_renderpass* renderpass;
} vulkan_framebuffer;

typedef struct vulkan_swapchain {
    VkSurfaceFormatKHR image_format;  // image format
    u8 max_frames_in_flight;          //
    VkSwapchainKHR handle;
    u32 image_count;
    VkImage* images;
    VkImageView* views;

    vulkan_image depth_attachment;
    // framebuffers used for on-screen rendering.
    vulkan_framebuffer* framebuffers;
} vulkan_swapchain;

typedef enum vulkan_command_buffer_state {
    COMMAND_BUFFER_STATE_READY,
    /*
    states the point when the commands are issued
    to the command buffer.
    */
    COMMAND_BUFFER_STATE_RECORDING,
    /*

    */
    COMMAND_BUFFER_STATE_IN_RENDER_PASS,
    /* states that recording is over*/
    COMMAND_BUFFER_STATE_RECORDING_ENDED,
    /* all the commands in the buffer has been completely
    executed. Occurs after RECORDING_ENDED state.
    */
    COMMAND_BUFFER_STATE_SUBMITTED,
    COMMAND_BUFFER_STATE_NOT_ALLOCATED
} vulkan_command_buffer_state;

// Holds a list of commands to be executed by a queue
typedef struct vulkan_command_buffer {
    VkCommandBuffer handle;

    // Command buffer state.
    vulkan_command_buffer_state state;
} vulkan_command_buffer;

/**
 *
 */
typedef struct vulkan_fence {
    VkFence handle;
    /**
     * Happens whenever we are waiting for a fence
     * and then that fence get signalled bec the operation has completed
     *
     */
    b8 is_signaled;
} vulkan_fence;

typedef struct vulkan_shader_stage {
    VkShaderModuleCreateInfo create_info;
    VkShaderModule handle;
    VkPipelineShaderStageCreateInfo shader_stage_create_info;
} vulkan_shader_stage;

typedef struct vulkan_pipeline {
    VkPipeline handle;
    VkPipelineLayout pipeline_layout;
} vulkan_pipeline;

#define OBJECT_SHADER_STAGE_COUNT 2
typedef struct vulkan_object_shader {
    // vertex, fragment
    vulkan_shader_stage stages[OBJECT_SHADER_STAGE_COUNT];

    vulkan_pipeline pipeline;

} vulkan_object_shader;

typedef struct vulkan_context {
    // The framebuffer's current width.
    u32 framebuffer_width;

    // The framebuffer's current height.
    u32 framebuffer_height;

    // Current generation of framebuffer size. If it does not match framebuffer_size_last_generation,
    // a new one should be generated.
    u64 framebuffer_size_generation;

    // The generation of the framebuffer when it was last created. Set to framebuffer_size_generation
    // when updated.
    u64 framebuffer_size_last_generation;

    VkInstance instance;
    VkAllocationCallbacks* allocator;
    VkSurfaceKHR surface;
#if defined(_DEBUG)
    VkDebugUtilsMessengerEXT debug_messenger;
#endif

    vulkan_device device;

    vulkan_swapchain swapchain;
    vulkan_renderpass main_renderpass;
    // darray
    vulkan_command_buffer* graphics_command_buffers;

    /**
     * Triggered when an image becomes available for rendering
     * this is when we're done presenting it
     */
    VkSemaphore* image_available_semaphores;  // darray

    /**
     * Triggered when a queue run against that and is now complete
     * and the queue is ready to be presented
     */
    VkSemaphore* queue_complete_semaphores;  // darray

    u32 in_flight_fence_count;
    vulkan_fence* in_flight_fences;

    // Holds pointers to fences which exist and are owned elsewhere.
    vulkan_fence** images_in_flight;  // in sync with current_frame

    // Currently used image's index
    u32 image_index;
    u32 current_frame;

    b8 recreating_swapchain;
    vulkan_object_shader object_shader;

    i32 (*find_memory_index)(u32 type_filter, u32 property_flags);

} vulkan_context;

#endif