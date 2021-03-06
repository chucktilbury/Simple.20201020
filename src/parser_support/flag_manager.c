/**
 * @file flag_manager.c
 * @brief This is a part of the parser_support library.
 *
 * This gives a "regular" way to access flags needed by the parser to maintine
 * it's state. There are 3 states that a flag can have: UNUSED, TRUE, and FALSE.
 * When something sets or clears a flag, then it becomes "used". A flag can be
 * returned to the unused state with a function call.
 *
 * Each flag is 2 bits. The top bit refers to the used state and the lower bit
 * refers to the boolean state of the flag.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-25
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "../include/common.h"

// define 32 flags to start with. If more flags are needed, then define
// another flags var and then implement the logic to tell the difference.
static uint64_t flags;

#define FLAG_INDEX(flag_number) ((flag_number) << 1)
#define FLAG_MASK(idx)  (0x3UL << FLAG_INDEX(idx))
#define FLAG_UBIT(idx)  (0x01UL << (FLAG_INDEX(idx)+1))
#define FLAG_VBIT(idx)  (0x01UL << FLAG_INDEX(idx))

/**
 * @brief Clear all flags to their UNUSED state.
 *
 */
void clear_flags(void) {

    flags = 0x00UL - 1;
}

/**
 * @brief Set the flag bit.
 *
 * @param flag -- Which flag.
 */
void set_flag(int flag) {

    // clear the unused bit
    flags &= ~FLAG_UBIT(flag);
    // set the value bit
    flags |= FLAG_VBIT(flag);

}

/**
 * @brief Clear the flag bit.
 *
 * @param flag -- Which flag.
 */
void clear_flag(int flag) {

    // clear the unused bit
    flags &= ~FLAG_UBIT(flag);
    // clear the value bit
    flags &= ~FLAG_VBIT(flag);

}

/**
 * @brief Reset the flag object to the UNUSED state.
 *
 * @param flag -- Which flag.
 */
void reset_flag(int flag) {

    flags |= FLAG_UBIT(flag);
    flags |= FLAG_VBIT(flag);

}

/**
 * @brief Get the flag object.
 *
 * @param flag -- Which flag.
 * @return int -- Return UNUSED, TRUE, or FALSE.
 */
int get_flag(int flag) {

    int v = (flags & FLAG_MASK(flag)) >> FLAG_INDEX(flag);
    if(v & 0x10)
        return(FM_UNUSED);
    else
        return(v);
}

// This data structure must match the order that the flags are defined in
static struct flag_strs{
    int flag;
    char* str;
} flag_strs[] = {
    {ENTRY_DEFINED, "ENTRY_DEFINED"},
    {CLASS_IS_ENTRY, "CLASS_IS_ENTRY"},
    {CONSTRUCTOR_DEFINED, "CONSTRUCTOR_DEFINED"},
    {DESTRUCTOR_DEFINED, "DESTRUCTOR_DEFINED"},
    {-1, NULL}
};

/**
 * @brief Convert the current flags into a printable string. Note
 * that the string must be free()'d.
 *
 */
char* flag_to_str(void) {

    char* outstr = strdup("(");
    for(int i = 0; flag_strs[i].str != NULL; i++) {
        if(get_flag(i)) {
            outstr = realloc_string(outstr, flag_strs[i].str);
            outstr = realloc_string(outstr, "|");
        }
    }

    if(strlen(outstr) == 1)
        outstr = realloc_string(outstr, "NONE ");
    outstr[strlen(outstr)-1] = ')';
    return(outstr);
}

