#ifndef KOHI_1700443356_RENDERER_FRONTEND_H
#define KOHI_1700443356_RENDERER_FRONTEND_H

#include "renderer_types.inl"

b8 renderer_system_initialize(u64* memory_requirement, void* state, const char* application_name);
void renderer_system_shutdown(void* state);

void renderer_on_resized(u16 width, u16 height);
// Runs once per frame and kicks off the rendering
b8 renderer_draw_frame(render_packet* packet);

#endif