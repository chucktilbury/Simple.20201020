/**
 * @file parser_support.h
 * @author Chuck Tilbury
 * @brief Header for function in the parser_support library.
 * @version 0.1
 * @date 2020-10-25
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __PARSER_SUPPORT_H__
#define __PARSER_SUPPORT_H__

#include <stdio.h>

/********************************
 * Definitions and prototypes for the code located in scanner.l
 */
char *get_file_name(void);
int get_line_number(void);
int get_col_number(void);
int open_file(const char *fname);
const char *get_tok_str(void);
int get_token(void);

/*
 * Defined by flex. Call one time to isolate a symbol and then use the global
 * symbol struct to access the symbol.
 */
extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;

// void yyerror(char *s, ...);
void yyerror(const char *s);

/************************************
 * Prototypes and data for compound names.
 */

// opaque handle for a compound name.
typedef void* compound_name;

compound_name create_compound_name(const char*);
void destroy_compound_name(compound_name);
void add_compound_name(compound_name, const char*);
const char* get_compound_name(compound_name);
const char* iterate_compound_name(compound_name);
void reset_compound_name(compound_name name);

/********************************************
 * Prototypes and data for the flag manager.
 */
typedef enum {FM_UNUSED = 0x03, FM_TRUE = 0x01, FM_FALSE = 0x00} flag_manager_state;
typedef enum {
    ENTRY_DEFINED,
    CLASS_IS_ENTRY,
    CONSTRUCTOR_DEFINED,
    DESTRUCTOR_DEFINED,
    PARSING_EXPRESSION,
} parser_flags;

void clear_flags(void);
void set_flag(int flag);
void clear_flag(int flag);
void reset_flag(int flag);
int get_flag(int flag);
char* flag_to_str(void);

/********************************************
 * Prototypes and data for the expression manager.
 */
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