/**
 * @file queue.h
 * @brief Definitions and prototypes for the queue.c file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

typedef void* queue;

int write_queue(queue, void*);
int read_queue(queue, void*);
int reset_queue(queue);
queue create_queue(size_t);
int destroy_queue(queue);

#endif

