/**
 * @file messages.c
 * @brief This file contains the code to write debugging messages to the
 * system console while the program runs for debugging purposes. This
 * depends on the debug.h file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifdef _DEBUGGING
#include "../include/common.h"
#include <stdarg.h>

static struct {
    int level;
    FILE* fp;
    const char* fname;
} debugging;

void init_debug(int level, const char* fname) {

    debugging.fname = fname;
    debugging.fp = fopen(fname, "w");
    if(debugging.fp == NULL) {
        fprintf(stderr, "Cannot open debug log: %s\n", fname);
        exit(1);
    }
    debugging.level = level;
}

void close_debug(void) {

    fclose(debugging.fp);
}

/**
 * @brief Print a simple generic debugging message.
 *
 * @param lev
 * @param str
 * @param ...
 */
void debug(int lev, char *str, ...) {

    va_list args;
    FILE *ofp;

    if(lev <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "DBG: ");
        va_start(args, str);
        vfprintf(ofp, str, args);
        va_end(args);
        fprintf(ofp, "\n");
    }
}

/**
 * @brief Print a generic debugging message.
 *
 * @param lev
 * @param str
 * @param ...
 */
void debug_msg(int lev, const char *str, ...) {

    va_list args;
    FILE *ofp;

    if(lev <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "MSG: %s: %d: %d: ", get_file_name(), get_line_number(), get_col_number());
        va_start(args, str);
        vfprintf(ofp, str, args);
        va_end(args);
        fprintf(ofp, "\n");
    }
}

/**
 * @brief Mark a spot in the code, related to the line and point in the
 * source code that is being traced.
 *
 * @param lev
 * @param file
 * @param line
 * @param func
 */
void debug_mark(int lev, const char *file, int line, const char *func) {

    FILE *ofp;

    if(lev <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "MARK: (%s, %d) %s: %d: %d: %s\n", clip_path(file), line, get_file_name(), get_line_number(), get_col_number(), func);
        //fprintf(ofp, "      %s: %d\n", file, line);
    }
}

/**
 * @brief Used to trace through the rules in the parser.
 *
 * @param lev
 * @param str
 * @param ...
 */
void debug_trace(int lev, const char *str, ...) {

    va_list args;
    FILE *ofp;

    if(lev <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "TRACE: %s: %d: %d: ", clip_path(get_file_name()), get_line_number(), get_col_number());
        va_start(args, str);
        vfprintf(ofp, str, args);
        va_end(args);
        fprintf(ofp, "\n");
    }
}

// #define INDENT_SPACES 2
// static int indent = 0;
/**
 * @brief All functions should be decorated with the macro associated with this.
 * It allows the stack trace to be printed in case of a seg fault or other
 * premature ending of the program.
 *
 * @param name
 * @param line
 */
void debug_entry(const char* name, int line) {

    //char buffer[100];
    FILE *ofp;

    if(20 <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "ENT: %s(): line %d\n", name, line);
        //indent += INDENT_SPACES;
    }
}

/**
 * @brief All return points in all functions should be decorated with the macros
 * associated with this function to enable stack tracing in the event of a
 * segfault or other premature ending of the program.
 *
 * @param name
 * @param line
 */
void debug_return(const char* name, int line) {

    FILE *ofp;

    if(20 <= debugging.level) {
        if(NULL != debugging.fp)
            ofp = debugging.fp;
        else
            ofp = stderr;

        fprintf(ofp, "RET: %s(): line %d\n", name, line);
    }
}

/**
 * @brief Exit the program and print the message.
 *
 * @param val
 */
void debug_exit(const char* fname, int line, const char* func, int val) {

    FILE *ofp;

    if(NULL != debugging.fp)
        ofp = debugging.fp;
    else
        ofp = stderr;

    fprintf(ofp, "EXIT: file %s: line %d: %s(): %d: ", clip_path(fname), line, func, val);
}

#endif /* _DEBUGGING */