
/*
 *  Errors
 *
 *  This contains the functions that show errors and warnings that result from
 *  parsing as well as those that result from things like memory allocation
 *  issues.
 */
#include <stdarg.h>

#include "common.h"

static struct errors {
    FILE *fp;
    int errors;
    int warnings;
} errors;

// messages longer than this will be truncated to this length.
char msg_buff[132];

/*
 *  Initialize the errors and logging system.
 */
void init_errors(FILE * stre) {

    errors.fp = stre; // If this is NULL, then stderr will be used.
    errors.errors = 0;
    errors.warnings = 0;
}

void inc_error_count(void) {
    errors.errors++;
}

void inc_warning_count(void) {
    errors.warnings++;
}

void set_error_stream(FILE * fp) {
    errors.fp = fp;
}

FILE *get_error_stream(void) {
    return errors.fp;
}

int get_num_errors(void) {
    return errors.errors;
}

int get_num_warnings(void) {
    return errors.warnings;
}

void syntax(char *str, ...) {

    va_list args;
    const char *name = get_file_name();
    int lnum = get_line_number();
    int col = get_col_number();

    if(lnum > 0)
        snprintf(msg_buff, sizeof(msg_buff), "Syntax Error: %s: %d: %d: ", name, lnum, col);
    else
        snprintf(msg_buff, sizeof(msg_buff), "Syntax Error: ");

    int len = strlen(msg_buff);
    va_start(args, str);
    vsnprintf(&msg_buff[len], sizeof(msg_buff)-len, str, args);
    va_end(args);
    errors.errors++;
    fprintf(stderr, "%s\n", msg_buff);
    _DEBUG(0, msg_buff);
}

void scanner_error(char *str, ...) {

    va_list args;
    const char *name = get_file_name();
    int lnum = get_line_number();
    int col = get_col_number();

    if(lnum > 0)
        snprintf(msg_buff, sizeof(msg_buff), "Scanner Error: %s: %d: %d: ", name, lnum, col);
    else
        snprintf(msg_buff, sizeof(msg_buff), "Scanner Error: ");

    int len = strlen(msg_buff);
    va_start(args, str);
    vsnprintf(&msg_buff[len], sizeof(msg_buff)-len, str, args);
    va_end(args);
    errors.errors++;
    fprintf(stderr, "%s\n", msg_buff);
    _DEBUG(0, msg_buff);
}

void warning(char *str, ...) {

    va_list args;
    const char *name = get_file_name();
    int lnum = get_line_number();
    int col = get_col_number();

    if(lnum > 0)
        snprintf(msg_buff, sizeof(msg_buff), "Warning: %s: %d: %d: ", name, lnum, col);
    else
        snprintf(msg_buff, sizeof(msg_buff), "Warning: ");

    int len = strlen(msg_buff);
    va_start(args, str);
    vsnprintf(&msg_buff[len], sizeof(msg_buff)-len, str, args);
    va_end(args);
    errors.warnings++;
    fprintf(stderr, "%s\n", msg_buff);
    _DEBUG(0, msg_buff);
}

/**
 * @brief This error is shown when one of those "impossible" errors happens.
 * For example, when some syntax is encountered that the parser should make
 * impossible.
 *
 * @param str
 * @param ...
 */
void internal_error(char *str, ...) {

    va_list args;

    snprintf(msg_buff, sizeof(msg_buff), "INTERNAL ERROR: ");

    int len = strlen(msg_buff);
    va_start(args, str);
    vsnprintf(&msg_buff[len], sizeof(msg_buff)-len, str, args);
    va_end(args);
    errors.errors++;
    fprintf(stderr, "%s\n", msg_buff);
    _DEBUG(0, msg_buff);
}

/**
 * @brief This is an error such as running out of memory. The exit handler
 * is still called, but the program is aborted.
 *
 * @param str
 * @param ...
 */
void fatal_error(char *str, ...) {

    va_list args;

    snprintf(msg_buff, sizeof(msg_buff), "FATAL ERROR: ");

    int len = strlen(msg_buff);
    va_start(args, str);
    vsnprintf(&msg_buff[len], sizeof(msg_buff)-len, str, args);
    va_end(args);
    errors.errors++;
    fprintf(stderr, "%s\n", msg_buff);
    _DEBUG(0, msg_buff);
}
