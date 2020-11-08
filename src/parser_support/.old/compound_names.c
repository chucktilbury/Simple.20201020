/**
 * @file compound_names.c
 * @brief This file contains code that the bison parser calls directly.
 *
 * This implements the compound name functionality. When a compound
 * name is parsed, it is read in segments. Each segment represents
 * a part of a path to follow to find the memory where the actual
 * object is located. This module facilitates storing the name in
 * a format that makes it easy to search, or to simply retrieve the
 * name as a single string.
 *
 * In the parser, it's possible that a compound name will not be consumed
 * immediately after it's parsed. The names are kept in stack until it's
 * consumed. When it's consumed, it's popped off of the stack and freed.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-25
 *
 * @copyright Copyright (c) 2020
 *
 */
//#undef _DEBUGGING
#include "../include/common.h"

typedef struct __cname {
    char* raw_name;
    struct __cname* next;
} _cname;

static _cname* name_stack = NULL;

/**
 * @brief Create a compound name object
 *
 * @param str
 */
void create_compound_name(const char* str) {

    _cname* cname = CALLOC(1, sizeof(_cname));
    cname->raw_name = STRDUP(str);
    _DEBUG(20, "create compound name \"%s\" (%p -> %p)", str, cname, name_stack);

    // push it on the stack
    cname->next = name_stack;
    name_stack = cname;
}

/**
 * @brief Destroy a compound name object. Caller has to free the string.
 *
 */
void destroy_compound_name(void) {

    _cname* cname = name_stack;

    if(cname != NULL) {
        // pop the top
        name_stack = cname->next;
        _DEBUG(20, "destroy compound name: \"%s\"", cname->raw_name);
        FREE(cname->raw_name);
        FREE(cname);
    }
    else
        internal_error("attempt to destroy a non-existant compound name");
}

/**
 * @brief Add a segment to the compound name.
 *
 * @param str -- The segment to add.
 */
void add_compound_name(const char* str) {

    _cname* cname = name_stack;
    char tmp[80];

    if(cname != NULL) {
        strcpy(tmp, ".");
        cat_string(tmp, str, sizeof(tmp));
        _DEBUG(20, "add to a compound name: \"%s\" -> \"%s\"", cname->raw_name, tmp);
        cname->raw_name = realloc_string(cname->raw_name, tmp);
    }
    else
        internal_error("attempt to add to a non-existant compound name");
}

/**
 * @brief Get the compound name object
 *
 * @return const char* -- The full name.
 */
const char* get_compound_name(void) {

    _cname* cname = name_stack;

    if(cname != NULL) {
        _DEBUG(20, "returning compound name: \"%s\"", cname->raw_name);
        return cname->raw_name;
    }
    else {
        internal_error("attempt to get to a non-existant compound name");
        return NULL;
    }
}

