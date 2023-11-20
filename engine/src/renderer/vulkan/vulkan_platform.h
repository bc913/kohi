#ifndef KOHI_1700456494_VULKAN_PLATFORM_H
#define KOHI_1700456494_VULKAN_PLATFORM_H

#include "defines.h"

/**
 * Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 */
void platform_get_required_extension_names(const char*** names_darray);

#endif