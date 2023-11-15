#ifndef KOHI_1699590192_PLATFORM_H
#define KOHI_1699590192_PLATFORM_H

#include "defines.h"

typedef struct platform_state {
    void* internal_state;
} platform_state;

// TODO: client should not see this methods keep it for now.
KAPI b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height);

KAPI void platform_shutdown(platform_state* plat_state);

// Will be called within the app loop
KAPI b8 platform_pump_messages(platform_state* plat_state);

// Memory
void* platform_allocate(u64 size, b8 aligned);
void platform_free(void* block, b8 aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* source, u64 size);
void* platform_set_memory(void* dest, i32 value, u64 size);
// Console
void platform_console_write(const char* message, u8 colour);
void platform_console_write_error(const char* message, u8 colour);
// Time
// Since application has actually been running
f64 platform_get_absolute_time();  // time in secs

// Sleep on the thread for the provided ms. This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// Therefore it is not exported.
void platform_sleep(u64 ms);

#endif