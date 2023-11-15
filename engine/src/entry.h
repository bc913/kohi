#ifndef KOHI_1700026096_ENTRY_H
#define KOHI_1700026096_ENTRY_H

#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"

#include <stdlib.h>

// Externally-defined function to create a game.
// We have included this and it is defined somewhere else out of this assembly
// User code should define this
extern b8 create_game(game* out_game);

/**
 * The main entry point of the application.
 */
int main(void) {
    // Request the game instance from the application.
    game game_inst;
    if (!create_game(&game_inst)) {
        KFATAL("Could not create game!", 0);
        return -1;
    }

    // Ensure the function pointers exist.
    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
        KFATAL("The game's function pointers must be assigned!", 0);
        return -2;
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        KINFO("Application failed to create!.", 0);
        return EXIT_FAILURE;
    }

    // Begin the game loop.
    if (!application_run()) {
        KINFO("Application did not shutdown gracefully.", 0);
        return 2;
    }

    return EXIT_SUCCESS;
}

#endif