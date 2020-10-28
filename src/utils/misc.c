/**
 * @file misc.c
 * @brief These routines are generic and used by many parts of the system.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-25
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#undef _DEBUGGING
#include "../include/utils.h"
#include "../include/configure.h"

/**
 * @brief This function works around the strncat() problem where the size is the length of the added
 * string, not the length of the total string. This accepts the length of the total string
 * and truncates the string to the maximum length if the added string would go over the
 * specified limit.
 *
 * @param dest -- Buffer to place the output into.
 * @param src -- The string to concatinate to the output.
 * @param size -- Size of the output buffer.
 * @return char* -- Pointer to the output buffer.
 */
char* cat_string(char* dest, const char* src, size_t size) {

    size_t s = strlen(dest)+1;

    return strncat(dest, src, size-s);
}

/**
 * @brief Return the part of a string past the last '/' that is foind it in it. The idea
 * is to return only a file name when presented with a path. If there is no '/'
 * in the string, then return the whole string. The original string is not altered
 * in any way.
 *
 * @param path -- Full path of the name to clip.
 * @return const char* -- The isolated file name.
 */
const char* clip_path(const char* path) {

    char* tmp = strrchr(path, '/');
    if(tmp != NULL)
        return ++tmp;
    else
        return path;
}

/**
 * @brief Locate the file name using the search path specified in configure.
 * If the file is found, then return a name that can be used by fopen.
 * If the file does not exist on dist, return NULL.
 *
 * @param fname -- File name to locate
 * @param outbuf -- Buffer to place the full path of the file into.
 * @param bsize -- Size of the output buffer
 * @return const char* -- NULL if there is an error, such as the file not existing.
 */
const char* find_file(const char* fname, char* outbuf, size_t bsize) {

    char* lst;

    reset_config_list("FPATH");
    while(NULL != (lst = iterate_config("FPATH"))) {
        strncpy(outbuf, lst, bsize);

        if(outbuf[strlen(outbuf)-1] != '/')
            cat_string(outbuf, "/", bsize);
        cat_string(outbuf, fname, bsize);

        int tlen = strlen(outbuf) - 2;
        _DEBUG("file ex = %s", &outbuf[tlen]);
        if(strcmp(&outbuf[tlen], ".s"))
            cat_string(outbuf, ".s", bsize);

        _DEBUG("checking file name: %s", outbuf);

        if(!access(outbuf, F_OK)) {
            _DEBUG("found file name: %s", outbuf);
            return outbuf;
        }
    }

    _DEBUG("no file was found");
    return NULL;
}

/**
 *  @brief Re allocate and cat a string.
 *  If the original is not NULL, then it is taken to having been allocated
 *  previously from the heap. If the original is NULL, then a new string is
 *  allocated for the newstr. If newstr is NULL, then the original is free'd.
 *  If there was no error, then the return value is a pointer to the new
 *  string. If there was an error, then the return value is NULL.
 *
 * @param orig -- The original string
 * @param newstr -- The string to concatinate
 * @return char* -- The new string
 */
char* realloc_string(const char* orig, const char* newstr) {

    _DEBUG("recat a string: orig = \"%s\", new = \"%s\"", orig, newstr);
    if(orig != NULL) {
        if(newstr == NULL)
            FREE((void*)orig);
        else {
            char* nptr = REALLOC((void*)orig, strlen(orig)+strlen(newstr)+2);
            if(nptr == NULL)
                fatal_error("cannot re-allocate memory for string");
            strcat(nptr, newstr);
            return nptr;
        }
    }
    else if(newstr != NULL) {
        char* nptr = STRDUP(newstr);
        if(nptr == NULL)
            fatal_error("cannot allocate new memory for string");
        return nptr;
    }

    return NULL;
}
