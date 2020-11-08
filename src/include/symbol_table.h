
#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

void push_name(const char* name);
void add_name(const char* name);
int pop_name(char* name, size_t len);
const char* peek_name(void);

#endif
