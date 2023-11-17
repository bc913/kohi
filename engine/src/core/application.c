#include "application.h"
#include "game_types.h"

#include "logger.h"

#include "platform/platform.h"
#include "core/kmemory.h"
#include "core/event.h"
#include "core/input.h"

typedef struct application_state {
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;  // no need to be a pointer
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

b8 application_create(game* game_inst) {
    if (initialized) {
        KERROR("application_create called more than once.", 0);
        return FALSE;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems before the game loop
    initialize_logging();
    input_initialize();

    // TODO: Remove this
    KFATAL("A test message: %f", 3.14f);
    KERROR("A test message: %f", 3.14f);
    KWARN("A test message: %f", 3.14f);
    KINFO("A test message: %f", 3.14f);
    KDEBUG("A test message: %f", 3.14f);
    KTRACE("A test message: %f", 3.14f);

    app_state.is_running = TRUE;
    // i.e. when you jump to other app in an Android device,
    // you should not consume the resources so this is the way to do that
    app_state.is_suspended = FALSE;

    if (!event_initialize()) {
        KERROR("Event system failed initialization. Application cannot continue.", 0);
        return FALSE;
    }

    if (!platform_startup(
            &app_state.platform,
            game_inst->app_config.name,
            game_inst->app_config.start_pos_x,
            game_inst->app_config.start_pos_y,
            game_inst->app_config.start_width,
            game_inst->app_config.start_height)) {
        return FALSE;
    }

    // Initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        KFATAL("Game failed to initialize.", 0);
        return FALSE;
    }

    // Hookup with event handlers
    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;
}

b8 application_run() {
    // get_memory_usage_str() is not portable due to strdup function call.
    // KINFO(get_memory_usage_str(), 0);

    while (app_state.is_running) {
        // if for any reason pump_messages returns false, just leave.
        if (!platform_pump_messages(&app_state.platform)) {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended) {
            // Update
            if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
                KFATAL("Game update failed, shutting down.", 0);
                app_state.is_running = FALSE;
                break;
            }

            // Call the game's render routine.
            if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                KFATAL("Game render failed, shutting down.", 0);
                app_state.is_running = FALSE;
                break;
            }

            /*
            Anything depends on given input, should always be handled before
            that input is actually recorded.

            The update will be available in the next frame
            */
            // NOTE: Input update/state copying should always be handled
            // after any input should be recorded; I.E. before this line.
            // As a safety, input is the last thing to be updated before
            // this frame ends.
            input_update(0);
            // this can be done before the update too
        }
    }

    // Shutdown
    app_state.is_running = FALSE;
    event_shutdown();
    input_shutdown();
    platform_shutdown(&app_state.platform);

    return TRUE;
}