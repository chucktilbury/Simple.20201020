/**
 * @file memory.h
 * @brief Dedinitions and macros for memory.c
 *
 * @author your name (you@domain.com)
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>

#define MALLOC(s) malloc_memory(s)
#define CALLOC(n, s) calloc_memory(n, s)
#define REALLOC(p, s) realloc_memory(p, s)
#define STRDUP(s) strdup_memory(s)
#define FREE(p) free_memory(p)

void init_memory(void);
void* malloc_memory(size_t size);
void* calloc_memory(size_t num, size_t size);
void* realloc_memory(void* ptr, size_t size);
char* strdup_memory(const char* str);
void free_memory(void* ptr);

#endif
