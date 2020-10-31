/**
 * @file expressions.h
 * @brief Prototypes and data for the expression manager.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __EXPRESSIONS_H__
#define __EXPRESSIONS_H__

typedef void* expression;

typedef enum {
    // value types
    EXP_NUMBER,
    EXP_STRING,
    EXP_BOOL,
    EXP_SYMBOL,
    EXP_SUBSCRIPTED,

    // arithmetic operators
    EXP_ADD_OPERATOR,
    EXP_SUB_OPERATOR,
    EXP_MUL_OPERATOR,
    EXP_DIV_OPERATOR,
    EXP_MOD_OPERATOR,

    // boolean operators
    EXP_EQU_OPERATOR,
    EXP_NEQU_OPERATOR,
    EXP_LT_OPERATOR,
    EXP_GT_OPERATOR,
    EXP_GTE_OPERATOR,
    EXP_LTE_OPERATOR,
    EXP_NOT_OPERATOR,
    EXP_AND_OPERATOR,
    EXP_OR_OPERATOR,

    // right-associating operators
    EXP_UNARY_PLUS,
    EXP_UNARY_MINUS,
    EXP_CAST,
} expression_element_types;

void create_expression(void);
void destroy_expression(void);
void add_expr_operator(int type);
void add_expr_number(const char* str);
void add_expr_bool(const char* str);
void add_expr_symbol(const char* str);
void add_expr_string(const char* str);
void add_expr_subscr(void);

void validate_expression(void);

#endif
