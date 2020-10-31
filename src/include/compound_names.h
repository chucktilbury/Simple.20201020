/**
 * @file compound_names.h
 * @brief Prototypes and data for compound names.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __COMPOUND_NAMES_H__
#define __COMPOUND_NAMES_H__

void create_compound_name(const char*);
void destroy_compound_name(void);
void add_compound_name(const char*);
const char* get_compound_name(void);

#endif

