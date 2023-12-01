#ifndef KOHI_1700024542_APPLICATION_H
#define KOHI_1700024542_APPLICATION_H

#include "defines.h"

//===========
// Definitions
//===========

struct game;

// Application configuration.
typedef struct application_config {
    // Window starting position x axis, if applicable.
    i16 start_pos_x;

    // Window starting position y axis, if applicable.
    i16 start_pos_y;

    // Window starting width, if applicable.
    i16 start_width;

    // Window starting height, if applicable.
    i16 start_height;

    // The application name used in windowing, if applicable.
    char* name;
} application_config;

//===========
// Methods
//===========

KAPI b8 application_create(struct game* game_inst);
// The game loop is in this function so it is gonna run
// unless an interruption occurs by the user or the system
KAPI b8 application_run();

void application_get_framebuffer_size(u32* width, u32* height);

#endif