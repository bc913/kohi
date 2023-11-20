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

#if defined(K_USE_VOLK_LOADER)

#if defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(__linux__) || defined(__unix__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(__APPLE__)
#define VK_USE_PLATFORM_MACOS_MVK
#else
#error "Platform not supported by this example."
#endif

#define VOLK_IMPLEMENTATION
#include "volk.h"

#else
#include <vulkan/vulkan.h>
#endif

typedef struct vulkan_context {
    VkInstance instance;
    VkAllocationCallbacks* allocator;
#if defined(_DEBUG)
    VkDebugUtilsMessengerEXT debug_messenger;
#endif
} vulkan_context;

#endif