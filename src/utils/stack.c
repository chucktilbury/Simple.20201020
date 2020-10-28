/**
 *  Simple implementation of a stack using linked lists, AKA a LIFO.
 *
 *  These routines manage their own memory. The out_buf parameter is a pointer to
 *  the data structure that is stored in the stack and functions like the pop and
 *  peek function copy the data into these buffers before possibly freeing it.
 *
 *  These functions return 0 for success and !0 for failure.
 */
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

typedef struct __stack_elem {
    void* data;
    struct __stack_elem* next;
} __stack_elem;

typedef struct {
    size_t item_size;
    __stack_elem* top;
} __stack;

/**
 *  Push an item on the stack. This allocates the memory for the stack item
 *  as well as the data that it contains. An error is returned when the
 *  memory cannot be allocated for the item or the data. Storing NULL data
 *  is not supported.
 */
int push_stack(stack stk, void* in_buf) {

    __stack* s = (__stack*)stk;

    __stack_elem* nelem = CALLOC(1, sizeof(__stack_elem));
    nelem->data = MALLOC(s->item_size);

    memcpy(nelem->data, in_buf, s->item_size);
    if(s->top == NULL) {
        s->top = nelem;
        // next and prev are NULL
    }
    else {
        nelem->next = s->top;
        s->top = nelem;
    }

    return 0;
}

/**
 *  Pop an item from the stack. The data is returned in the void* parameter.
 *  If there was an error, then return !0, otherwise return 0. If the out_buf
 *  parameter is NULL, then the data is simply discarded, instead of copied
 *  into the buffer.
 */
int pop_stack(stack stk, void* out_buf) {

    __stack* s = (__stack*)stk;
    __stack_elem* old_elem = s->top;

    if(s->top != NULL) {
        if(out_buf != NULL) {
            memcpy(out_buf, s->top->data, s->item_size);
        } // else just discard any data
        FREE(s->top->data);
        s->top = s->top->next;
        FREE(old_elem);
        return 0;
    }

    return 1;
}

/**
 *  Return the data structure on the top of the stack without altering
 *  the stack itself.
 */
int peek_stack(stack stk, void* out_buf) {

    __stack* s = (__stack*)stk;

    if(s->top != NULL) {
        memcpy(out_buf, s->top->data, s->item_size);
        return 0;
    }

    return 1;
}

/**
 *  Returns TRUE if stack is empty.
 */
int stack_is_empty(stack stk) {

    __stack* s = (__stack*)stk;
    return (s->top == NULL);
}

/**
 *  Allocate the stack data structure on the heap and return the opaque
 *  handle. If the memory allocation fails, then return NULL.
 */
stack create_stack(size_t size) {

    __stack* stk = CALLOC(1, sizeof(__stack));

    stk->item_size = size;
    // top is NULL
    return (stack)stk;
}

/**
 *  Free all of the memory associated with the stack.
 */
int destroy_stack(stack stk) {

    while(!stack_is_empty(stk)) {
        pop_stack(stk, NULL);
    }
    FREE(stk);
    return 0;
}

