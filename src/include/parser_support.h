/*
 *  Header for compound names.
 */
#ifndef __COMPOUND_NAMES_H__
#define __COMPOUND_NAMES_H__

// opaque handle
typedef void* compound_name;

compound_name create_compound_name(const char*);
void destroy_compound_name(compound_name);
void add_compound_name(compound_name, const char*);
const char* get_compound_name(compound_name);
const char* iterate_compound_name(compound_name);
void reset_compound_name(compound_name name);

#endif