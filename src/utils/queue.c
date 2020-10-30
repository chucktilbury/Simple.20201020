/*
 *  This is a simple implementation of a queue. New elements are added to the
 *  end and reads happen from the beginning. This is AKA a FIFO.
 *
 *  Elements that are stored in the FIFO are copied into local memory. Functions
 *  that read the data have a buffer parameter to which the data is copies.
 *
 *  These functions return 0 for success and !0 for failure.
 */
#include <stdio.h>
#include <string.h>
//#undef _DEBUGGING
#include "../include/utils.h"

typedef struct __queue_elem {
    void* data;
    struct __queue_elem* next;
} __queue_elem;

typedef struct {
    size_t item_size;
    __queue_elem* base;
    __queue_elem* crnt;
    __queue_elem* last;
} __queue;

/*
 *  Add an element to the end of the queue. Returns an error only when
 *  memory cannot be allocated for the queue element.
 */
int write_queue(queue que, void* in_buf) {

    _MARK();
    __queue* q = (__queue*)que;
    // MALLOC() and CALLOC() end the program if they fail.
    __queue_elem* nelem = CALLOC(1, sizeof(__queue_elem));
    _DEBUG("item size = %lu", q->item_size);
    nelem->data = MALLOC(q->item_size);

    memcpy(nelem->data, in_buf, q->item_size);
    if(q->base == NULL) {
        q->base = q->crnt = q->last = nelem;
    }
    else {
        q->last->next = nelem;
        q->last = nelem;
    }

    return 0;
}

/*
 *  Read from the head of the queue. If the queue is empty or if the last
 *  item has been read then return !0, else return 0.
 */
int read_queue(queue que, void *out_buf) {

    _MARK();
    __queue* q = (__queue*)que;
    if(q->crnt != NULL) {
        memcpy(out_buf, q->crnt->data, q->item_size);
        q->crnt = q->crnt->next;
        return 0;
    }
    return 1;
}

/*
 *  This resets the current pointer to the beginning of the queue. No other
 *  elements are effected. Alwats returns no error, even if the queue is
 *  empty.
 */
int reset_queue(queue que) {

    _MARK();
    __queue* q = (__queue*)que;
    q->crnt = q->base;
    return 0;
}

/*
 *  Return an opaque handle to the queue. The element size is the amount of
 *  memory to be allocated for the data in the queue. If memory cannot be
 *  allocated the return NULL.
 */
queue create_queue(size_t elem_size) {

    _MARK();
    __queue* q = (__queue*)CALLOC(1, sizeof(__queue));

    q->item_size = elem_size;
    // base and crnt are NULL
    return q;
}

/*
 *  Free all memory associated with the queue. The only error condition is
 *  when the queue pointer is NULL.
 */
int destroy_queue(queue que) {

    _MARK();
    __queue* q = (__queue*)que;
    __queue_elem* crnt;
    __queue_elem* next;

    if(q != NULL) {
        for(crnt = q->base; crnt != NULL; crnt = next) {
            next = crnt->next;
            if(crnt->data != NULL) {
                FREE(crnt->data);
            }
            FREE(crnt);
        }
        FREE(q);
        return 0;
    }
    return 1;
}

