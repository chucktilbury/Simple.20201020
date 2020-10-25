/*
 *  This file contains code that the bison parser calls directly.
 *
 *  This implements the compound name functionality. When a compound
 *  name is parsed, it is read in segments. Each segment represents
 *  a part of a path to follow to find the memory where the actual
 *  object is located. This module facilitates storing the name in
 *  a format that makes it easy to search, or to simply retrieve the
 *  name as a single string.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef _DEBUGGING
#include "../include/parser_support.h"
#include "../include/lists.h"
#include "../include/errors.h"
#include "../include/misc.h"
#include "../include/memory.h"

typedef struct __cname {
    char* raw_name;
    list_t segments;
} _cname;


compound_name create_compound_name(const char* str) {

    _cname* cn = (_cname*)CALLOC(1, sizeof(_cname));
    if(cn == NULL)
        fatal_error("cannot allocate memory for compound name");

    _DEBUG("create compound name: %s", str);
    init_list(&cn->segments);
    cn->raw_name = realloc_string(NULL, str);
    append_list(&cn->segments, STRDUP(str));

    return (compound_name)cn;
}

void destroy_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;

    _DEBUG("destroy compound name: %s", cn->raw_name);
    reset_list(&cn->segments);
    void* item;
    while(NULL != (item = get_list_next(&cn->segments))) {
        _DEBUG("free segment: %s", item);
        FREE(item);
    }
    FREE(cn->segments.buffer);
    FREE(cn);
}

void add_compound_name(compound_name name, const char* str) {

    _cname* cn = (_cname*)name;
    char tmp[80];

    _DEBUG("add to compound name: %s", str);
    strcpy(tmp, ".");
    cat_string(tmp, str, sizeof(tmp));

    cn->raw_name = realloc_string(cn->raw_name, tmp);
    append_list(&cn->segments, STRDUP(str));
}

const char* get_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    return cn->raw_name;
}

const char* iterate_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    return get_list_next(&cn->segments);
}

void reset_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    reset_list(&cn->segments);
}