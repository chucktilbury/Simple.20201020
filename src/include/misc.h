/**
 * @file misc.h
 * @brief Definitions and prototypes for the misc.c file.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __MISC_H__
#define __MISC_H__

#include <stdlib.h>

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

#endif
