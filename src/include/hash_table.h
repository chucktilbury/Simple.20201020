/**
 * @file hash_table.h
 * @brief Definitions and prototypes for the hash_table.c file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdlib.h>

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

#endif