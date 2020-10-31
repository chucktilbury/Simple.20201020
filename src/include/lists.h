/**
 * @file lists.h
 * @brief Definitions and prototypes for the lists.c file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __LISTS_H__
#define __LISTS_H__

#include <stdlib.h>

typedef struct
{
    size_t nitems;      // number of items currently in the array
    size_t index;       // current index for iterating the list
    size_t capacity;    // capacity in items
    void** buffer;      // raw buffer where the items are kept
} list_t;

void init_list(list_t* list);
list_t* create_list(void);
void destroy_list(list_t* array);
void append_list(list_t* array, void* item);
void* get_list_by_index(list_t* array, int index);
void* get_list_next(list_t* lst);
void reset_list(list_t* lst);

#endif
