#include <stdio.h>
#include <stdlib.h>

#include "../include/scanner.h"
#include "../parser/parser.h"
//#include "../include/utils.h"
#include "../include/configure.h"
#include "../include/errors.h"

//#include "ast_tree.h"

// note that longer vars with the same leading letters need to appear before shorter ones.
BEGIN_CONFIG
    CONFIG_NUM("-v", "VERBOSE", "Set the verbosity from 0 to 50", 0, 0, 0)
    CONFIG_STR("-o", "OUTFILE", "Specify the file name to output", 0, "output.bc", 1)
    CONFIG_LIST("-i", "FPATH", "Specify directories to search for imports", 0, ".:include", 0)
    CONFIG_BOOL("-D", "DFILE_ONLY", "Output the dot file only. No object output", 0, 0, 0)
    CONFIG_STR("-d", "DUMP_FILE", "Specify the file name to dump the AST into", 0, "ast_dump.dot", 1)
END_CONFIG


int main(int argc, char **argv) {
    init_errors(10, stdout);
    configure(argc, argv);
    int verbose = GET_CONFIG_NUM("VERBOSE");

    //init_ast();
    for(char* str = iterate_config("INFILES"); str != NULL; str = iterate_config("INFILES")) {
        _DEBUG("before yyparse()");
        open_file(str);
        yyparse();
        _DEBUG("after yyparse()");
    }

    int errors = get_num_errors();

    if(errors != 0)
        printf("\nparse failed: %d errors: %d warnings\n", errors, get_num_warnings());
    else
        printf("\nparse succeeded: %d errors: %d warnings\n", errors, get_num_warnings());

    return errors;
}
