/**
 * @file expressions.c
 * @brief Expressions are organized into RPN order by the Bison parser. This
 * module records the expression in a queue for solution later. The solution
 * is then handled using a stack as one would expect. Expressions that have
 * been created are accessed through an opaque handle. Expressions should have
 * the memory freed with the destroy function when they are garbage collected.
 *
 * Expressions can be nested. This can happen, for example, when a
 * formatted_string is part of another expression. Expressions are kept in a
 * stack. When the expression is destroyed, it is popped off of the stack.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-28
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "../include/common.h"

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

/*
 * The stack stores the first element in the expression queue.
 */
static _expr_list* expr_stack;
static int stack_created = 0;

/**
 * @brief Convert a string to a double with error checking.
 *
 * @param str -- string to convert.
 * @return double -- value returned.
 */
static inline double _string_to_num(const char * str) {

    char* end;
    double val = strtod(str, &end);

    if(str == end) {
        scanner_error("cannot convert string to number: \"%s\"", str);
    }
    return(val);
}

/**
 * @brief Create a expression object and push it to the top of the stack.
 */
void create_expression(void) {

    _expr_list* expr_lst = (_expr_list*)CALLOC(1, sizeof(_expr_list));

    if(stack_created) {
        expr_lst->next = expr_stack;
        expr_stack = expr_lst;
    }
    else {
        expr_stack = expr_lst;
    }
}

/**
 * @brief Destroy the expression at the top of the stack and free all
 * of the memory associated with it. Use this when garbage collecting.
 */
void destroy_expression(void) {

    if(expr_stack != NULL) {
        // pop the top of the stack
        _expr_list* old_top = expr_stack;
        expr_stack = expr_stack->next;

        // free the list
        _expr_element* next;
        _expr_element* crnt = old_top->first;
        for( crnt = old_top->first; crnt!= NULL; crnt = next) {
            next = crnt->next;
            if(crnt->type == EXP_STRING || crnt->type == EXP_SYMBOL)
                FREE(crnt->str);
            FREE(crnt);
        }

        // free the old_top
        FREE(old_top);
    }
    else {
        fatal_error("attempt to destroy a non-existant expression");
    }
}

/**
 * @brief Add an operator to the expression list.
 *
 * @param type -- The type of operator to add.
 */
void add_expr_operator(int type) {

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = type;

        expr_stack->last->next = elem;
        expr_stack->last = elem;
    }
    else {
        fatal_error("attempt to add expression operator to empty expression stack");
    }
}

/**
 * @brief Add a literal number to the queue.
 *
 * @param str -- The string that represents the number.
 */
void add_expr_number(const char* str) {

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_NUMBER;
        elem->number = _string_to_num(str);

        expr_stack->last->next = elem;
        expr_stack->last = elem;
    }
    else {
        fatal_error("attempt to add expression number literal to empty expression stack");
    }
}

/**
 * @brief Add a literal boolean value to the queue.
 *
 * @param str -- The string that represents the bool value.
 */
void add_expr_bool(const char* str) {

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));
        elem->type = EXP_BOOL;

        int val = -1;
        if(!strcmp(str, "true"))
            val = 1;
        else if(!strcmp(str, "false"))
            val = 0;
        else
            fatal_error("attempt to convert a non-boolean literal to a boolean value");

        elem->bool_val = val;

        expr_stack->last->next = elem;
        expr_stack->last = elem;
    }
    else {
        fatal_error("attempt to add expression boolean literal to empty expression stack");
    }
}

/**
 * @brief Add a symbol reference to the queue.
 *
 * @param str -- String the represents the symbol table key of the symbol.
 */
void add_expr_symbol(const char* str) {

    if(expr_stack != NULL) {
        _DEBUG(11, "here 1: %p", expr_stack);
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));
        _DEBUG(11, "here 2");
        elem->type = EXP_SYMBOL;
        _DEBUG(11, "here 3");
        elem->str = STRDUP(str);
        _DEBUG(11, "here 4");

        expr_stack->last->next = elem;
        _DEBUG(11, "here 5");
        expr_stack->last = elem;
        _DEBUG(11, "here 6");
    }
    else {
        fatal_error("attempt to add expression symbol to empty expression stack");
    }
}

/**
 * @brief Add a literal string to the queue.
 *
 * @param str -- The string to evaluate.
 */
void add_expr_string(const char* str) {

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));
        elem->type = EXP_STRING;
        elem->str = STRDUP(str);

        expr_stack->last->next = elem;
        expr_stack->last = elem;
    }
    else {
        fatal_error("attempt to add expression string literal to empty expression stack");
    }
}

/**
 * @brief Add a subscripted symbol to the queue. The expression evaluator must
 * be reentrant because this will involve evaluating a sub-expression for the
 * subscript.
 *
 * (implementing later)
 */
void add_expr_subscr(void) {
    fatal_error("subscripted expression elements not supported yet.");
}


/**
 * @brief This function makes sure that the expression can be solved from
 * a semantic point of view. For example, it does not make any sense to add
 * a number to a string without a cast.
 */
void validate_expression(void) {
    _TRACE("validating the expression");
}