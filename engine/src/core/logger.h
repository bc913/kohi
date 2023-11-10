#ifndef KOHI_1696173210_LOGGER_H
#define KOHI_1696173210_LOGGER_H

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release
#if KRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
    LOG_LEVEL_FATAL = 0, /*Application crash*/
    LOG_LEVEL_ERROR = 1, /*Serious error but application can still run*/
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4, /*Only in debug*/
    LOG_LEVEL_TRACE = 5  /*Only in debug*/
} log_level;

b8 initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char* message, ...);

// Logs a fatal level message
#if defined(_MSC_VER)
#define KFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, __VA_ARGS__);
#else
#define KFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#endif

// Logs an ERROR message
#ifndef KERROR
#if defined(_MSC_VER)
#define KERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, __VA_ARGS__);
#else
#define KERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif
#endif

// Warning level
#if LOG_WARN_ENABLED == 1
#if defined(_MSC_VER)
#define KWARN(message, ...) log_output(LOG_LEVEL_WARN, message, __VA_ARGS__);
#else
#define KWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#endif
#else
// does nothing when LOG_WARN_ENABLED != 1
#define KWARN(message, ...)
#endif

// Info
#if LOG_INFO_ENABLED == 1
#if defined(_MSC_VER)
#define KINFO(message, ...) log_output(LOG_LEVEL_INFO, message, __VA_ARGS__);
#else
#define KINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#endif
#else
// does nothing when LOG_INFO_ENABLED != 1
#define KINFO(message, ...)
#endif

// DEBUG
#if LOG_DEBUG_ENABLED == 1
#if defined(_MSC_VER)
#define KDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, __VA_ARGS__);
#else
#define KDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#endif
#else
// does nothing when LOG_DEBUG_ENABLED != 1
#define KDEBUG(message, ...)
#endif

// Trace
#if LOG_TRACE_ENABLED == 1
#if defined(_MSC_VER)
#define KTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, __VA_ARGS__);
#else
#define KTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#endif
#else
// does nothing when LOG_TRACE_ENABLED != 1
#define KTRACE(message, ...)
#endif

#endif  // KOHI_1696173210_LOGGER_H