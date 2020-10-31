/**
 * @file memory.c
 * @brief This is a wrapper for memory routines. When there is a memory error, the
 * program is aborted.
 *
 * In the future this will have hooks to track memory use for things like
 * finding out what line in the code a particular block was allocated from
 * and whether all memory has been freed.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-27
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "../include/common.h"

#define GETSEG(p) (unsigned int)((((uint64_t)(p)) & 0xFFFF00000000) >> 32)

static unsigned int stack_segment = 0;
static unsigned int heap_segment = 0;

void init_memory(void) {

    int num;
    stack_segment = GETSEG(&num);
    heap_segment = GETSEG(&heap_segment);

    //_DEBUG(11, "stack = %p, heap = %p", &num, &heap_segment);
    _DEBUG(11, "stack = 0x%04X, heap = 0x%04X", stack_segment, heap_segment);
}

void* malloc_memory(size_t size) {

    void* ptr = malloc(size);
    if(ptr == NULL)
        fatal_error("malloc cannot allocate %lu bytes", size);

    return(ptr);
}

void* calloc_memory(size_t num, size_t size) {

    void* ptr = calloc(num, size);
    if(ptr == NULL)
        fatal_error("calloc cannot allocate %lu bytes", num*size);

    return(ptr);
}

void* realloc_memory(void* ptr, size_t size) {

    void* nptr = NULL;

    if(GETSEG(ptr) == heap_segment)
         nptr = realloc(ptr, size);
    else
        fatal_error("attempt to reallocate memory not allocated by malloc. (0x%04X)", GETSEG(ptr));

    if(nptr == NULL)
        fatal_error("realloc cannot allocate %lu bytes", size);

    return(nptr);
}

char* strdup_memory(const char* str) {

    char* nstr = strdup(str);
    if(nstr == NULL)
        fatal_error("strdup cannot allocate %lu bytes", strlen(str));

    return(nstr);
}

// note that the heap and the bss segments have the same signature under Linux.
void free_memory(void* ptr) {

    if(GETSEG(ptr) == heap_segment)
        free(ptr);
    else
        fatal_error("attempt to free memory not allocated by malloc. (0x%04X)", GETSEG(ptr));
}
