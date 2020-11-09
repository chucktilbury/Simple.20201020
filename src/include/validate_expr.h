#ifndef __VALIDATE_EXPR_H__
#define __VALIDATE_EXPR_H__

#include "expressions.h"

int _comparison(int op);
int _compare_lr(_expr_element* left, _expr_element* right);
int _arithmetic(int op);
int _arith_lr(_expr_element* left, _expr_element* right);
void _expr_push(_expr_element* elem);
void _expr_push_error(void);
int _expr_pop(_expr_element* elem);
_expr_element* _expr_peek(void);

int validate_expression(void);

#endif
