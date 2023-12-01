#ifndef KOHI_1701463951_VULKAN_FENCE_H
#define KOHI_1701463951_VULKAN_FENCE_H

#include "vulkan_types.inl"

/**
 * create_signaled = true means this is already signaled so don't wait for it
 */
void vulkan_fence_create(
    vulkan_context* context,
    b8 create_signaled,
    vulkan_fence* out_fence);

void vulkan_fence_destroy(vulkan_context* context, vulkan_fence* fence);

b8 vulkan_fence_wait(vulkan_context* context, vulkan_fence* fence, u64 timeout_ns);

void vulkan_fence_reset(vulkan_context* context, vulkan_fence* fence);

#endif