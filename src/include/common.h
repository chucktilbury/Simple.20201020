#ifndef __COMMON_H__
#define __COMMON_H__

#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "misc.h"
#include "scanner.h"
#include "memory.h"
#include "errors.h"
#include "hash_table.h"
#include "lists.h"
//#include "data_lists.h"
#include "stack.h"
#include "queue.h"
//#include "ast.h"
#include "../parser/parser.h"
#include "configure.h"
//#include "symbol_table.h"

extern memory_system_t* memory_system;

#endif
