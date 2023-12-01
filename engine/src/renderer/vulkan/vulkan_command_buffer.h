#ifndef KOHI_1701452772_VULKAN_COMMAND_BUFFER_H
#define KOHI_1701452772_VULKAN_COMMAND_BUFFER_H

#include "vulkan_types.inl"
/*
command buffers are allocated from the command pool
*/
void vulkan_command_buffer_allocate(
    vulkan_context* context,
    VkCommandPool pool,
    b8 is_primary,
    vulkan_command_buffer* out_command_buffer);

/*
Frees the command buffer to go back to the pool.
It does not deallocate the command buffer.
*/
void vulkan_command_buffer_free(
    vulkan_context* context,
    VkCommandPool pool,
    vulkan_command_buffer* command_buffer);

/*
Begins recording the commands to the command buffer to be issued later
*/
void vulkan_command_buffer_begin(
    vulkan_command_buffer* command_buffer,
    b8 is_single_use,
    b8 is_renderpass_continue,
    b8 is_simultaneous_use);

/**
 * Ends recording
 */
void vulkan_command_buffer_end(vulkan_command_buffer* command_buffer);

void vulkan_command_buffer_update_submitted(vulkan_command_buffer* command_buffer);

void vulkan_command_buffer_reset(vulkan_command_buffer* command_buffer);

/**
 * Allocates and begins recording to out_command_buffer.
 * Sometimes we only need single use command (buffer)
 * Assumption: The command buffer is primary
 */
void vulkan_command_buffer_allocate_and_begin_single_use(
    vulkan_context* context,
    VkCommandPool pool,
    vulkan_command_buffer* out_command_buffer);

/**
 * Ends recording, submits to and waits for queue operation and frees the provided command buffer.
 */
void vulkan_command_buffer_end_single_use(
    vulkan_context* context,
    VkCommandPool pool,
    vulkan_command_buffer* command_buffer,
    VkQueue queue);

/*
commands -> commands buffer --> appropriate queue
command buffers are allocated withing the command pool.
command buffers can not be created only be allocated within the pools

the command pools should be created and when they're destroyed the commands are deallocated automatically.
*/

#endif