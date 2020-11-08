
#include "common.h"

typedef struct __token_stack {
    int token;
    struct __token_stack* next;
} _token_stack;

_token_stack* token_stack;

void push_token(int token) {

    _token_stack* ts = (_token_stack*)CALLOC(1, sizeof(_token_stack));
    ts->token = token;
    ts->next = token_stack;
    token_stack = ts;
}

int pop_token(void) {

    int retv = -1;
    if(token_stack != NULL) {
        _token_stack* ts = token_stack;
        retv = ts->token;
        token_stack = ts->next;
        FREE(ts);
    }
    return retv;
}

int peek_token(void) {

    if(token_stack != NULL)
        return token_stack->token;
    else
        return -1;
}
