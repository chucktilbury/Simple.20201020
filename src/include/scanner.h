/**
 * @file scanner.h
 * @brief Definitions and prototypes for the code located in scanner.l
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdio.h>
#include "../parser/parser.h"

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

#ifdef _DEBUGGING
#define TYPE_TO_STR(t) \
        ((t == DICT)? "DICT": \
        (t == LIST)? "LIST": \
        (t == BOOL)? "BOOL": \
        (t == STRING)? "STRING": \
        (t == FLOAT)? "FLOAT": \
        (t == INTEGER)? "INTEGER": \
        (t == SYMBOL)? "SYMBOL": "UNKNOWN")
#endif

#endif

