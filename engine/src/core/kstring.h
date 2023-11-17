#ifndef KOHI_1700190151_KSTRING_H
#define KOHI_1700190151_KSTRING_H

#include "defines.h"

// Returns the length of the given string.
KAPI u64 string_length(const char* str);

KAPI char* string_duplicate(const char* str);

#endif