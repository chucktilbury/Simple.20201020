

#include "common.h"

typedef struct __str_stack {
    const char* str;
    struct __str_stack* next;
} _str_stack;

static _str_stack* str_stack;

void push_name(const char* name) {

    _DEBUG(40, "push_name: %s", name);
    _str_stack* nss = CALLOC(1, sizeof(_str_stack));
    nss->str = STRDUP(name);

    nss->next = str_stack;
    str_stack = nss;
}

void add_name(const char* name) {

    _DEBUG(40, "add_name: %s", name);
    if(str_stack != NULL) {
        realloc_string(str_stack->str, ".");
        realloc_string(str_stack->str, name);
    }
}

int pop_name(char* name, size_t len) {

    if(str_stack != NULL) {
        _str_stack* nss = str_stack;
        if(name != NULL)
            strncpy(name, nss->str, len);
        _DEBUG(40, "pop_name: %s", nss->str);

        str_stack = nss->next;
        FREE((void*)nss->str);
        FREE(nss);
        return 1;   // success
    }
    return 0;   // failed
}

const char* peek_name(void) {

    if(str_stack != NULL) {
        return str_stack->str;
    }

    return NULL;
}
