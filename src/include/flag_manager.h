/**
 * @file flag_manager.h
 * @brief Prototypes and data for the flag manager.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __FLAG_MANAGER_H__
#define __FLAG_MANAGER_H__

typedef enum {FM_UNUSED = 0x03, FM_TRUE = 0x01, FM_FALSE = 0x00} flag_manager_state;
typedef enum {
    ENTRY_DEFINED,
    CLASS_IS_ENTRY,
    CONSTRUCTOR_DEFINED,
    DESTRUCTOR_DEFINED,
    PARSING_EXPRESSION,
} parser_flags;

void clear_flags(void);
void set_flag(int flag);
void clear_flag(int flag);
void reset_flag(int flag);
int get_flag(int flag);
char* flag_to_str(void);

#endif

