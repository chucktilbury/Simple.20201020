/**
 * @file debug.h
 * @brief This header defined macros that are used for debugging, however
 * it must be included in release code because it defines macros that are
 * used to switch between debugging and release builds.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

// TODO: Add more macros for debugging and memory tracking.
#ifdef _DEBUGGING
#  define _MARK() debug_mark(12, __FILE__, __LINE__, __func__)
#  define _DEBUG(...) debug(11, __VA_ARGS__)
#  define _TRACE(...) debug_trace(6, __VA_ARGS__)
#  define _TRACE1(...) debug_trace(7, __VA_ARGS__)
#  define _TRACE2(...) debug_trace(8, __VA_ARGS__)
#  define _TRACE3(...) debug_trace(9, __VA_ARGS__)
#  define _TRACE4(...) debug_trace(10, __VA_ARGS__)
void debug_mark(int, const char*, int, const char *);
void debug_trace(int, const char *, ...);
void debug(int level, char* str, ...);
#else
#  define _MARK()
#  define _DEBUG(...)
#  define _TRACE(...)
#  define _TRACE1(...)
#  define _TRACE2(...)
#  define _TRACE3(...)
#  define _TRACE4(...)
#endif


void init_debug(int level, const char* fname);
void close_debug(void);

#endif /* __DEBUG_H__ */