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
} parser_flags;

void clear_flags(void);
void set_flag(int flag);
void clear_flag(int flag);
void reset_flag(int flag);
int get_flag(int flag);
char* flag_to_str(void);

#endif