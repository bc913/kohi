#ifndef KOHI_1702260059_RESOURCE_TYPES_H
#define KOHI_1702260059_RESOURCE_TYPES_H

#include "math/math_types.h"

typedef struct texture {
    u32 id;
    u32 width;
    u32 height;
    u8 channel_count;
    b8 has_transparency;
    u32 generation;
    void* internal_data;
} texture;

#endif