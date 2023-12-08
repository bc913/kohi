#ifndef KOHI_1702008827_VULKAN_OBJECT_SHADER_H
#define KOHI_1702008827_VULKAN_OBJECT_SHADER_H

#include "renderer/vulkan/vulkan_types.inl"
#include "renderer/renderer_types.inl"

b8 vulkan_object_shader_create(vulkan_context* context, vulkan_object_shader* out_shader);

void vulkan_object_shader_destroy(vulkan_context* context, struct vulkan_object_shader* shader);

void vulkan_object_shader_use(vulkan_context* context, struct vulkan_object_shader* shader);

#endif