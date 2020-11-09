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
    int type;
    int cast_type;
    char* str;
    double fpnum;
    long long intnum;
    int bool_val;
    struct _expr_element* next;
} _expr_element;

typedef struct _expr_list {
    _expr_element* first;
    _expr_element* last;
    struct _expr_list* next;
} _expr_list;


//typedef void* expression;

typedef enum {
    EXP_FIRST_ENTRY = 100,

    // value types
    EXP_FLOAT = EXP_FIRST_ENTRY,
    EXP_INT,
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
    //EXP_CAST_TYPE,

    EXP_ERROR,
} expression_element_types;

#ifdef _DEBUGGING
#define EXPR_TYPE_TO_STR(v) \
        ((EXP_FLOAT == (v))? "EXP_FLOAT": \
        (EXP_INT == (v))? "EXP_INT": \
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
        (EXP_ERROR == (v))? "EXP_ERROR": "UNKNOWN")
        //(EXP_CAST_TYPE == (v))? "EXP_CAST_TYPE": "UNKNOWN")
#endif

//void create_expression(void);
void destroy_expression(void);
void add_expr_operator(int type);
void add_expr_cast(int type);
void add_expr_float(double num);
void add_expr_int(long long num);
void add_expr_true(void);
void add_expr_false(void);
void add_expr_symbol(const char* str);
void add_expr_string(const char* str);
void add_expr_subscr(void);

void clear_expr_flags(void);

#endif
