#ifndef KOHI_1700190151_KSTRING_H
#define KOHI_1700190151_KSTRING_H

#include "defines.h"

// Returns the length of the given string.
KAPI u64 string_length(const char* str);

KAPI char* string_duplicate(const char* str);

// Case-sensitive string comparison. True if the same, otherwise false.
KAPI b8 strings_equal(const char* str0, const char* str1);

#endif