#include "logger.h"
#include "asserts.h"
// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MESSAGE_SIZE 32000

b8 initialize_logging() {
    // TODO: create log file
    return TRUE;
}

void shutdown_logging() {
    // TODO: cleanup logging /write queued entries
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    // b8 is_error = level < 2;

    // Technically imposes a 32k character limit on a single log entry, but...
    // DON'T DO THAT!
    // No dynamic memory allocation
    char out_message[MESSAGE_SIZE];
    memset(out_message, 0, sizeof(out_message));

    // Format original message
    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, MESSAGE_SIZE, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[MESSAGE_SIZE];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    // TODO: platform_specific output
    printf("%s", out_message2);
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}