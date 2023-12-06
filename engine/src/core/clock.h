#ifndef KOHI_1700440543_CLOCK_H
#define KOHI_1700440543_CLOCK_H

#include "defines.h"

typedef struct clock {
    f64 start_time;  // when the clock is started
    f64 elapsed;     // secs
} clock;

// Updates the provided clock. Should be called just before checking elapsed time.
// Has no effect on non-started clocks.
KAPI void clock_update(clock* clock);

// Starts the provided clock. Resets elapsed time.
KAPI void clock_start(clock* clock);

// Stops the provided clock. Does not reset elapsed time.
KAPI void clock_stop(clock* clock);

#endif