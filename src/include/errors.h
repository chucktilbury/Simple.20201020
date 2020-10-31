/**
 * @file errors.h
 * @brief Definitions and prototypes for the errors.c file.
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __ERRORS_H__
#define __ERRORS_H__
#include <stdio.h>

void init_errors(int level, FILE* fp);
void syntax(char* str, ...);
void system_error(char *str, ...);
void scanner_error(char* str, ...);
void warning(char* str, ...);
void fatal_error(char* str, ...);

void set_logging_level(int lev);
int get_logging_level(void);
int get_num_errors(void);
int get_num_warnings(void);
void set_error_level(int lev);
int get_error_level(void);
void set_error_stream(FILE* fp);
FILE* get_error_stream(void);
void inc_error_count(void);
void inc_warning_count(void);

#endif