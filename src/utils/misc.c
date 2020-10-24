
//#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#undef _DEBUGGING
#include "../include/configure.h"
#include "../include/errors.h"

/*
 * This function works around the strncat() problem where the size is the length of the added
 * string, not the length of the total string. This accepts the length of the total string
 * and truncates the string to the maximum length if the added string would go over the
 * specified limit.
 */
char* cat_string(char* dest, const char* src, size_t size) {

    size_t s = strlen(dest)+1;

    return strncat(dest, src, size-s);
}

const char* clip_path(const char* path) {

    char* tmp = strrchr(path, '/');
    if(tmp != NULL)
        return ++tmp;
    else
        return path;
}

/*
 * Locate the file name using the search path specified in configure.
 *
 * If the file is found, then return a name that can be used by fopen,
 * otherwise return NULL.
 */
const char* find_file(const char* fname, char* outbuf, size_t bsize) {

    char* lst;

    reset_config_list("FPATH");
    while(NULL != (lst = iterate_config("FPATH"))) {
        strncpy(outbuf, lst, bsize);

        if(outbuf[strlen(outbuf)-1] != '/')
            cat_string(outbuf, "/", bsize);
        cat_string(outbuf, fname, bsize);

        if(outbuf[strlen(outbuf)-1] != 's' && outbuf[strlen(outbuf)-2] != '.')
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