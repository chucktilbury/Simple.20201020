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
 * The stack stores the first element in the expression queue.
 */
_expr_list* expr_stack;
static int stack_created = 0;

/**
 * @brief Convert a string to a double with error checking.
 *
 * @param str -- string to convert.
 * @return double -- value returned.
 */
static inline double _string_to_float(const char * str) {

    char* end;
    double val = strtod(str, &end);

    if(str == end) {
        scanner_error("cannot convert string to number: \"%s\"", str);
    }
    return(val);
}

/**
 * @brief Convert a string to a double with error checking.
 *
 * @param str -- string to convert.
 * @return double -- value returned.
 */
static inline long _string_to_int(const char * str) {

    char* end;
    long long val = strtoll(str, &end, 10);

    if(str == end) {
        scanner_error("cannot convert string to number: \"%s\"", str);
    }
    return(val);
}

/**
 * @brief Add an element to the expression list.
 */
static inline void add_element(_expr_element* elem) {

    // have already validated that the TOS is valid.
    if(expr_stack->first == NULL) {
        expr_stack->first = elem;
        expr_stack->last = elem;
    }
    else {
        expr_stack->last->next = elem;
        expr_stack->last = elem;
    }
}

/**
 * @brief Create a expression object and push it to the top of the stack.
 */
static inline void create_expression(void) {

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
 * @brief Set the expression flags before an "add".
 */
static inline void set_expr_flags(void) {

    if(!get_flag(PARSING_EXPRESSION)) {
        create_expression();
        set_flag(PARSING_EXPRESSION);
    }
}

/**
 * @brief Set the expression flags before an "add".
 */
void clear_expr_flags(void) {
    clear_flag(PARSING_EXPRESSION);
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

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = type;

        add_element(elem);
    }
    else {
        fatal_error("attempt to add expression operator to empty expression stack");
    }
}

/**
 * @brief Add an operator to the expression list.
 *
 * @param type -- The type of operator to add.
 */
void add_expr_cast(int type) {

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_CAST;
        elem->apparent_type = type;

        add_element(elem);
    }
    else {
        fatal_error("attempt to add expression operator to empty expression stack");
    }
}

/**
 * @brief Add a literal number to the queue.
 */
void add_expr_float(double num) {

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_FLOAT;
        elem->fpnum = num;

        add_element(elem);
    }
    else {
        fatal_error("attempt to add expression number literal to empty expression stack");
    }
}

/**
 * @brief Add a literal number to the queue.
 */
void add_expr_int(long long num) {

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_INT;
        elem->intnum = num;

        add_element(elem);
    }
    else {
        fatal_error("attempt to add expression number literal to empty expression stack");
    }
}

/**
 * @brief Add a literal boolean value to the queue.
 *
 */
void add_expr_true(void) {

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_BOOL;
        elem->bool_val = 1;

        add_element(elem);
    }
    else {
        fatal_error("attempt to add expression boolean literal to empty expression stack");
    }
}

/**
 * @brief Add a literal boolean value to the queue.
 *
 */
void add_expr_false(void) {

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_BOOL;
        elem->bool_val = 0;

        add_element(elem);
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

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));

        elem->type = EXP_SYMBOL;
        elem->str = STRDUP(str);

        add_element(elem);
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

    set_expr_flags();

    if(expr_stack != NULL) {
        _expr_element* elem = (_expr_element*)CALLOC(1, sizeof(_expr_element));
        elem->type = EXP_STRING;
        elem->str = STRDUP(str);

        add_element(elem);
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

