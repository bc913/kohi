#ifndef KOHI_1700442937_RENDERER_TYPES_INL
#define KOHI_1700442937_RENDERER_TYPES_INL

#include "defines.h"

typedef enum renderer_backend_type {
    RENDERER_BACKEND_TYPE_VULKAN,
    RENDERER_BACKEND_TYPE_OPENGL,
    RENDERER_BACKEND_TYPE_DIRECTX
} renderer_backend_type;

// Renderer implementations will fill out these function impls
typedef struct renderer_backend {
    struct platform_state* plat_state;
    u64 frame_number;

    // Initialize
    b8 (*initialize)(struct renderer_backend* backend, const char* application_name, struct platform_state* plat_state);
    // Shutdown
    void (*shutdown)(struct renderer_backend* backend);
    // Action against window resize (against new width and height)
    void (*resized)(struct renderer_backend* backend, u16 width, u16 height);
    // Frame ops
    b8 (*begin_frame)(struct renderer_backend* backend, f32 delta_time);
    b8 (*end_frame)(struct renderer_backend* backend, f32 delta_time);
} renderer_backend;

// The data that renderer needs to know to draw things
typedef struct render_packet {
    f32 delta_time;
} render_packet;

#endif