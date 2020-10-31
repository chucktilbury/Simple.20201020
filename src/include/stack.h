/**
 * @file stack.h
 * @brief Definitions and prototypes for the stack.c file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

typedef void* stack;

int push_stack(stack, void*);
int pop_stack(stack, void*);
int peek_stack(stack, void*);
int stack_is_empty(stack);
stack create_stack(size_t);
int destroy_stack(stack);

#endif

