/**
 * @file utils.h
 * @brief This contains the combined headers for the utils library.

 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-27
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * Definitions and prototypes for the errors.c file.
 */
void init_errors(int level, FILE* fp);
void syntax(char* str, ...);
//int expect_token(scanner_state_t*ss, int expect);
//int expect_token_list(scanner_state_t* ss, int num, ...);
void system_error(char *str, ...);
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

// TODO: Add more macros for debugging and memory tracking.
#ifdef _DEBUGGING

#define _MARK() debug_mark(6, __FILE__, __LINE__, __func__)
#define _TRACE(...) debug_trace(6, __VA_ARGS__)
#define _DEBUG(...) debug(5, __VA_ARGS__)

#else

#define _MARK()
#define _TRACE(...)
#define _DEBUG(...)

#endif

/******************************************************************************
 * Definitions and prototypes for the hash_table.c file.
 */
enum
{
    HASH_NO_ERROR,
    HASH_EXIST,
    HASH_NOT_FOUND,
    HASH_NO_DATA,
    HASH_DATA_SIZE,
};

typedef struct
{
    const char* key;
    size_t size;
    void* data;
} _table_entry_t;

typedef struct
{
    size_t count;
    size_t capacity;
    _table_entry_t* entries;
} hash_table_t;

hash_table_t* create_hash_table(void);
void destroy_hash_table(hash_table_t* table);
int insert_hash_table(hash_table_t* table, const char* key, void* data, size_t size);
int find_hash_table(hash_table_t* table, const char* key, void* data, size_t size);
size_t find_hash_table_entry_size(hash_table_t* tab, const char* key);
const char* iterate_hash_table(hash_table_t* tab, int reset);

/******************************************************************************
 * Definitions and prototypes for the lists.c file.
 */
typedef struct
{
    size_t nitems;      // number of items currently in the array
    size_t index;       // current index for iterating the list
    size_t capacity;    // capacity in items
    void** buffer;      // raw buffer where the items are kept
} list_t;

void init_list(list_t* list);
list_t* create_list(void);
void destroy_list(list_t* array);
void append_list(list_t* array, void* item);
void* get_list_by_index(list_t* array, int index);
void* get_list_next(list_t* lst);
void reset_list(list_t* lst);

/******************************************************************************
 * Definitions and prototypes for the queue.c file.
 */
typedef void* queue;

int write_queue(queue, void*);
int read_queue(queue, void*);
int reset_queue(queue);
queue create_queue(size_t);
int destroy_queue(queue);

/******************************************************************************
 * Definitions and prototypes for the stack.c file.
 */
typedef void* stack;

int push_stack(stack, void*);
int pop_stack(stack, void*);
int peek_stack(stack, void*);
int stack_is_empty(stack);
stack create_stack(size_t);
int destroy_stack(stack);

/******************************************************************************
 * Definitions and prototypes for the misc.c file.
 */
/*
 * This macro works around the strncat() problem where the size is the length of the added
 * string, not the length of the total string. This accepts the length of the total string
 * and truncates the string to the maximum length if the added string would go over the
 * specified limit.
 */
#define STRNCAT(dest, src, size) strncat((dest), (src), size-strlen(dest))
char* cat_string(char* dest, const char* src, size_t size);

/*
 * Clip the path to the main file name.
 */
const char* clip_path(const char* path);

/*
 *  Find a file in the path provided by config.
 */
const char* find_file(const char* fname, char* outbuf, size_t bsize);

/*
 *  Re-allocate a string.
 */
char* realloc_string(const char* orig, const char* newstr);

/******************************************************************************
 * Definitions for memory macros
 */
#define MALLOC(s) malloc_memory(s)
#define CALLOC(n, s) calloc_memory(n, s)
#define REALLOC(p, s) realloc_memory(p, s)
#define STRDUP(s) strdup_memory(s)
#define FREE(p) free_memory(p)
void init_memory(void);
void* malloc_memory(size_t size);
void* calloc_memory(size_t num, size_t size);
void* realloc_memory(void* ptr, size_t size);
char* strdup_memory(const char* str);
void free_memory(void* ptr);


#endif /* __UTILS_H__ */