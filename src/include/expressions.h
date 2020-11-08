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

/*
 * This same data structure is used when parsing an expression and when it
 * is being evaluated. This is a private data structure.
 */
typedef struct _expr_element {
    // This is the parsed element type. If the element is a number, it will
    // keep this type as it is evaluated.
    int type;

    // Used when evaluating to keep track of the current apparent type. For
    // example, if two strings are being compared, then this will be bool.
    int apparent_type;

    // If the element is a symbol, then this is the symbol table key. If the
    // element is a literal string, then this is a pointer to it.
    char* str;

    // If the element is a literal number then this is the value. This is the
    // value that is pushed on the stack durning evaluation for numeric
    // expressions.
    double number;

    // This is the value that is pushed on the stack for boolean apparent values.
    int bool_val;

    // This is the next element in the expression element list.
    struct _expr_element* next;

} _expr_element;

typedef struct _expr_list {
    _expr_element* first;
    _expr_element* last;
    struct _expr_list* next;
} _expr_list;


//typedef void* expression;

typedef enum {
    // value types
    EXP_NUMBER = 100,
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
    EXP_CAST_TYPE,

    EXP_ERROR,
} expression_element_types;

#ifdef _DEBUGGING
#define EXPR_TYPE_TO_STR(v) \
        ((EXP_NUMBER == (v))? "EXP_NUMBER": \
        (EXP_STRING == (v))? "EXP_STRING": \
        (EXP_BOOL == (v))? "EXP_BOOL": \
        (EXP_SYMBOL == (v))? "EXP_SYMBOL": \
        (EXP_SUBSCRIPTED == (v))? "EXP_SUBSCRIPTED": \
        (EXP_ADD_OPERATOR == (v))? "EXP_ADD_OPERATOR": \
        (EXP_SUB_OPERATOR == (v))? "EXP_SUB_OPERATOR": \
        (EXP_MUL_OPERATOR == (v))? "EXP_MUL_OPERATOR": \
        (EXP_DIV_OPERATOR == (v))? "EXP_DIV_OPERATOR": \
        (EXP_MOD_OPERATOR == (v))? "EXP_MOD_OPERATOR": \
        (EXP_EQU_OPERATOR == (v))? "EXP_EQU_OPERATOR": \
        (EXP_NEQU_OPERATOR == (v))? "EXP_NEQU_OPERATOR": \
        (EXP_LT_OPERATOR == (v))? "EXP_LT_OPERATOR": \
        (EXP_GT_OPERATOR == (v))? "EXP_GT_OPERATOR": \
        (EXP_GTE_OPERATOR == (v))? "EXP_GTE_OPERATOR": \
        (EXP_LTE_OPERATOR == (v))? "EXP_LTE_OPERATOR": \
        (EXP_NOT_OPERATOR == (v))? "EXP_NOT_OPERATOR": \
        (EXP_AND_OPERATOR == (v))? "EXP_AND_OPERATOR": \
        (EXP_OR_OPERATOR == (v))? "EXP_OR_OPERATOR": \
        (EXP_UNARY_PLUS == (v))? "EXP_UNARY_PLUS": \
        (EXP_UNARY_MINUS == (v))? "EXP_UNARY_MINUS": \
        (EXP_CAST == (v))? "EXP_CAST": \
        (EXP_ERROR == (v))? "EXP_ERROR": \
        (EXP_CAST_TYPE == (v))? "EXP_CAST_TYPE": "UNKNOWN")
        #endif

//void create_expression(void);
void destroy_expression(void);
void add_expr_operator(int type);
void add_expr_cast(int type);
void add_expr_number(const char* str);
void add_expr_true(void);
void add_expr_false(void);
void add_expr_symbol(const char* str);
void add_expr_string(const char* str);
void add_expr_subscr(void);

void clear_expr_flags(void);

#endif
