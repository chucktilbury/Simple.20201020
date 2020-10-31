
/*
 *  Errors
 *
 *  This contains the functions that show errors and warnings that result from
 *  parsing as well as those that result from things like memory allocation
 *  issues.
 */
#include <stdarg.h>

#include "../include/common.h"

static struct errors {
    FILE *fp;
    int errors;
    int warnings;
} errors;

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

    if(lnum > 0)
        fprintf(stderr, "Syntax Error: %s: %d: ", name, lnum);
    else
        fprintf(stderr, "Syntax Error: ");

    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    errors.errors++;
}

void scanner_error(char *str, ...) {

    va_list args;
    const char *name = get_file_name();
    int lnum = get_line_number();

    if(lnum > 0)
        fprintf(stderr, "Scanner Error: %s: %d: ", name, lnum);
    else
        fprintf(stderr, "Scanner Error: ");

    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    errors.errors++;
}

void warning(char *str, ...) {

    va_list args;
    const char *name = get_file_name();
    int lnum = get_line_number();

    if(lnum > 0)
        fprintf(stderr, "Warning: %s: %d: ", name, lnum);
    else
        fprintf(stderr, "Warning: ");

    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    errors.warnings++;
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

    fprintf(stderr, "INTERNAL ERROR: ");

    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    errors.errors++;
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

    fprintf(stderr, "FATAL ERROR: ");
    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    errors.errors++;

    exit(1);
}

