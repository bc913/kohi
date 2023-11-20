#ifndef KOHI_1700443356_RENDERER_FRONTEND_H
#define KOHI_1700443356_RENDERER_FRONTEND_H

#include "renderer_types.inl"

// Fwd decls
struct static_mesh_data;
struct platform_state;

b8 renderer_initialize(const char* application_name, struct platform_state* plat_state);
void renderer_shutdown();

void renderer_on_resized(u16 width, u16 height);
// Runs once per frame and kicks off the rendering
b8 renderer_draw_frame(render_packet* packet);

#endif