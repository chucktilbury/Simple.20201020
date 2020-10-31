/**
 * @file compound_names.c
 * @brief This file contains code that the bison parser calls directly.
 *
 *  This implements the compound name functionality. When a compound
 *  name is parsed, it is read in segments. Each segment represents
 *  a part of a path to follow to find the memory where the actual
 *  object is located. This module facilitates storing the name in
 *  a format that makes it easy to search, or to simply retrieve the
 *  name as a single string.
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
    list_t segments;
} _cname;

/**
 * @brief Create a compound name object
 *
 * @param str
 * @return compound_name
 */
compound_name create_compound_name(const char* str) {

    _cname* cn = (_cname*)CALLOC(1, sizeof(_cname));
    if(cn == NULL)
        fatal_error("cannot allocate memory for compound name");

    _DEBUG(11, "create compound name: %s", str);
    init_list(&cn->segments);
    cn->raw_name = realloc_string(NULL, str);
    append_list(&cn->segments, STRDUP(str));

    return((compound_name)cn);
}

/**
 * @brief Destroy a compound name object
 *
 * @param name -- The compound name to destroy
 */
void destroy_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;

    _DEBUG(11, "destroy compound name: %s", cn->raw_name);
    reset_list(&cn->segments);
    void* item;
    while(NULL != (item = get_list_next(&cn->segments))) {
        _DEBUG(11, "free segment: %s", item);
        FREE(item);
    }
    FREE(cn->segments.buffer);
    FREE(cn);
}

/**
 * @brief Add a segment to the compound name.
 *
 * @param name -- The compound name to add to.
 * @param str -- The segment to add.
 */
void add_compound_name(compound_name name, const char* str) {

    _cname* cn = (_cname*)name;
    char tmp[80];

    _DEBUG(11, "add to compound name: %s", str);
    strcpy(tmp, ".");
    cat_string(tmp, str, sizeof(tmp));

    cn->raw_name = realloc_string(cn->raw_name, tmp);
    append_list(&cn->segments, STRDUP(str));
}

/**
 * @brief Get the compound name object
 *
 * @param name -- The compound name object to query
 * @return const char* -- The full name.
 */
const char* get_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    return(cn->raw_name);
}

/**
 * @brief Scan the compound name, one segment at a time.
 *
 * @param name -- The compound name to iterate.
 * @return const char* -- The segment that weas iterated, or NULL if there are no more segments.
 */
const char* iterate_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    return(get_list_next(&cn->segments));
}

/**
 * @brief Reset the compound name iterator. This must be called before
 * the compound name is iterated.
 *
 * @param name -- The compound name to iterate.
 */
void reset_compound_name(compound_name name) {

    _cname* cn = (_cname*)name;
    reset_list(&cn->segments);
}

