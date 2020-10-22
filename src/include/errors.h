/*
 *  Errors header
 */
#ifndef _ERRORS_H_
#define _ERRORS_H_

/*
 * TODO: Add macros for debugging and memory tracking.
 */
#include <stdio.h>

void init_errors(int level, FILE* fp);
void syntax(char* str, ...);
//int expect_token(scanner_state_t*ss, int expect);
//int expect_token_list(scanner_state_t* ss, int num, ...);
void scanner_error(char* str, ...);
void warning(char* str, ...);
void debug(int level, char* str, ...);
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

void debug_mark(int, const char*, int, const char *);
void debug_trace(int, const char *, ...);

/*
 * TODO: Add more macros for debugging and memory tracking.
 */
#ifdef _DEBUGGING

#define _MARK() debug_mark(6, __FILE__, __LINE__, __func__)
#define _TRACE(...) debug_trace(6, __VA_ARGS__)
#define _DEBUG(...) debug(5, __VA_ARGS__)

#else

#define _MARK()
#define _TRACE(...)
#define _DEBUG(...)

#endif


#endif /* _ERRORS_H_ */
