/**
 * @file simple.c
 * @brief This is the main entry point to the compiler.
 *
 * @author Chuck Tilbury
 * @version 0.1
 * @date 2020-10-31
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <signal.h>

//#undef _DEBUGGING
#include "../include/common.h"
#include "../parser/parser.h"

//#include "ast_tree.h"

// note that longer vars with the same leading letters need to appear before shorter ones.
BEGIN_CONFIG
    CONFIG_NUM("-v", "VERBOSE", "Set the verbosity from 0 to 50", 0, 0, 0)
    CONFIG_STR("-o", "OUTFILE", "Specify the file name to output", 0, "output.bc", 1)
    CONFIG_LIST("-i", "FPATH", "Specify directories to search for imports", 0, ".:include", 0)
    CONFIG_BOOL("-D", "DFILE_ONLY", "Output the dot file only. No object output", 0, 0, 0)
    CONFIG_STR("-d", "DUMP_FILE", "Specify the file name to dump the AST into", 0, "ast_dump.dot", 1)
    CONFIG_STR("-l", "LOG_FILE", "Specify the file name to dump the logging information into", 0, "debug.log", 1)
END_CONFIG

static void segfault_handler(int sig) {

    (void)sig;
    fprintf(stderr, "\nSystem SEGFAULT\n");
    inc_error_count();
    exit(1);
}

static void exit_func(void) {
    int errors = get_num_errors();

    if(errors != 0)
        printf("\nparse failed: %d errors: %d warnings\n\n", errors, get_num_warnings());
    else
        printf("\nparse succeeded: %d errors: %d warnings\n\n", errors, get_num_warnings());

    destroy_config();
    close_debug();
}

static void init_all(int argc, char** argv) {

    signal(SIGSEGV, segfault_handler);
    init_memory();  // configure uses the routines in memory.c
    configure(argc, argv);
    init_errors(NULL); // errors go to stderr
    init_debug(GET_CONFIG_NUM("VERBOSE"), GET_CONFIG_STR("LOG_FILE"));
    //init_ast();

    if(atexit(exit_func))
        fatal_error("cannot add exit function");
}

int main(int argc, char **argv) {

    init_all(argc, argv);

    for(char* str = iterate_config("INFILES"); str != NULL; str = iterate_config("INFILES")) {
        _DEBUG(11, "     >>> before yyparse()");
        if(open_file(str)) {
            syntax("cannot continue");
            break;
        }

        yyparse();
        _DEBUG(11, "     >>> after yyparse()");
    }

    return(get_num_errors());
}
