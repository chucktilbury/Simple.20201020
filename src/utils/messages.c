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

/**
 * @brief Init the debug code. This sets the level of the debug messages and
 * also opens the debugger logging file.
 *
 * @param level
 * @param fname
 */
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
 * @brief Print a simple generic debugging message with no information about
 * the source code or the file being parsed.
 *
 * @param lev
 * @param str
 * @param ...
 */
void debug(int lev, const char *str, ...) {

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
 * @brief Print a generic debugging message with information about the file
 * that is being parsed.
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


#endif /* _DEBUGGING */