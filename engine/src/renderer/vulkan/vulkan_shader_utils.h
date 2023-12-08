#ifndef KOHI_1702008971_VULKAN_SHADER_UTILS_H
#define KOHI_1702008971_VULKAN_SHADER_UTILS_H

#include "vulkan_types.inl"

b8 create_shader_module(
    vulkan_context* context,
    const char* name,
    const char* type_str,
    VkShaderStageFlagBits shader_stage_flag,
    u32 stage_index,
    vulkan_shader_stage* shader_stages);

#endif