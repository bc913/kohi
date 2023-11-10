#ifndef KOHI_1696707785_ASSERTS_H
#define KOHI_1696707785_ASSERTS_H

#include "defines.h"

/*
// Cross-platform impl for debug
https://github.com/scottt/debugbreak/blob/master/debugbreak.h
*/

// comment out to disable assertions
#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED

#if _MSC_VER
// TODO: This works for now
// #include <intrin.h>
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

KAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define KASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            DEBUG_BREAK();                                           \
        }                                                            \
    }

#define KASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            DEBUG_BREAK();                                                \
        }                                                                 \
    }

#ifdef _DEBUG
#define KASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            DEBUG_BREAK();                                           \
        }                                                            \
    }
#else                        //_DEBUG
#define KASSERT_DEBUG(expr)  // Does nothing at all
#endif                       //_DEBUG

#else                               // KASSERTIONS_ENABLED
#define KASSERT(expr)               // Does nothing at all
#define KASSERT_MSG(expr, message)  // Does nothing at all
#define KASSERT_DEBUG(expr)         // Does nothing at all
#endif

#endif  // KOHI_1696707785_ASSERTS_H