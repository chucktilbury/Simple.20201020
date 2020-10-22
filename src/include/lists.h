#ifndef __LISTS_H__
#define __LISTS_H__
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Structure for a managed array.
 */
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
