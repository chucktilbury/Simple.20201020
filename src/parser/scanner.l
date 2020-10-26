
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#undef _DEBUGGING

#include "parser.h"
#include "../include/errors.h"
#include "../include/misc.h"

//#undef _TRACE
//#define _TRACE(...)

// maximum depth of imports prevents crashing from circular imports.
static int import_depth = 0;
#define MAX_IMPORTS 15

// string buffer to get token from
static char strbuf[1024*64];

typedef struct _file_name_stack {
    int line_no;
    int col_no;
    char *name;
    struct _file_name_stack *next;
} _file_name_stack;

void count(void);
static char buffer[1024*64];
static int bidx = 0;
static _file_name_stack *name_stack;
int num_errors = 0; // global updated by parser

// these funcs support the string scanner
static void append_char(char ch) {
    if((sizeof(buffer)-1) > bidx) {
        buffer[bidx] = ch;
        bidx++;
    }
    else {
        scanner_error("buffer overrun");
        //fprintf(stderr, "scanner buffer overrun");
        exit(1);
    }
}

static void append_str(char *str) {
    if((sizeof(buffer)-1) > (strlen(buffer) + strlen(str))) {
        strcat(buffer, str);
        bidx = strlen(buffer);
    }
    else {
        scanner_error("buffer overrun");
        //fprintf(stderr, "scanner buffer overrun");
        exit(1);
    }
}

static void update_loc(void){

    if(NULL != name_stack) {
        yylloc.first_line   = name_stack->line_no;
        yylloc.first_column = name_stack->col_no;
    }
    else
        return;

    for(char *s = yytext; *s != '\0'; s++) {
        name_stack->col_no++;
    }

    yylloc.last_line   = name_stack->line_no;
    yylloc.last_column = name_stack->col_no-1;
}

#define YY_USER_ACTION update_loc();
//#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

DIGIT   [0-9]
SYMCH   [a-zA-Z_$@%^&!~?#|]

/* state definitions */
%x SQUOTES
%x DQUOTES
%x COMMENT
%option noinput nounput
%option yylineno
%option noyywrap
%%

    /* overhead */
\n              { name_stack->line_no++; name_stack->col_no=1; } // yylineno++; }
[ \t\r]         {}

    /* keywords */
"nothing"       { return NOTHING; }
"import"        { return IMPORT; }
"constructor"   { return CONSTRUCT; }
"destructor"    { return DESTRUCT; }
"destroy"       { return DESTROY; }
"string"        { return STRING; }
"number"        { return NUMBER; }
"dict"          { return DICT; }
"list"          { return LIST; }
"bool"          { return BOOL; }
"true"          { return TRUE; }
"false"         { return FALSE; }
"for"           { return FOR; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"do"            { return DO; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"default"       { return DEFAULT; }
"entry"         { return ENTRY; }
"Entry"         { return ENTRY; }

    /* boolean operator tokens composed of special characters */
"and"           { return AND; }
"or"            { return OR; }

"not"           { return NOT; }
"equ"           { return EQU; }
"neq"           { return NEQU; }
"leq"           { return LTEQU; }
"geq"           { return GTEQU; }
"lt"            { return LESS; }
"gt"            { return MORE; }

    /* arithmetic operators */
"-"             { return '-'; }
"+"             { return '+'; }
"="             { return '='; }
"/"             { return '/'; }
"*"             { return '*'; }
"%"             { return '%'; }

    /* Other operators */
","             { return ','; }
";"             { return ';'; }
":"             { return ':'; }
"["             { return '['; }
"]"             { return ']'; }
"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
"."             { return '.'; }

    /* constructed tokens */
    /* [_A-Za-z][_0-9A-Za-z]*    { _TRACE("SCANNER: symbol scan: %s",yytext); strncpy(strbuf, yytext, sizeof(strbuf)); return SYMBOL; } */
{SYMCH}({SYMCH}|{DIGIT})* { _TRACE("SCANNER: symbol scan: %s",yytext); strncpy(strbuf, yytext, sizeof(strbuf)); return SYMBOL; }
    /* [_A-Za-z][_0-9A-Za-z\.]*    { strncpy(strbuf, yytext, sizeof(strbuf)); return COMPLEX; } */

    /* recognize and ignore comments */
"<-" { BEGIN(COMMENT); _TRACE("SCANNER: start multi-line comment"); }
<COMMENT>"->" { BEGIN(INITIAL); _TRACE("SCANNER: end multi-line comment"); }
<COMMENT>\n { name_stack->line_no++; yylineno++; }
<COMMENT>.  {}  /* eat everything in between */

"<<".* { _TRACE("SCANNER: single-line comment"); }  /* eat up until the newline */

    /* recognize a float */
    /*[-+]?[0-9]+\.[0-9]+([eE]*[-+]?[0-9]+)? { */
[0-9]+(\.[0-9]+([eE]+[-+]?[0-9]+)?)? {
        _TRACE("SCANNER: number scanned: %s", yytext);
        strncpy(strbuf, yytext, sizeof(strbuf));
        return NUM;
    }

    /* double quoted strings have escapes managed */
\"  {
        bidx = 0;
        memset(buffer, 0, sizeof(buffer));
        BEGIN(DQUOTES);
    }

<DQUOTES>\" {
        strncpy(strbuf, buffer, sizeof(strbuf));
        BEGIN(INITIAL);
        return QSTRG;
    }

    /* the short rule matches before the long one does */
<DQUOTES>\\n    { append_char('\n'); }
<DQUOTES>\\r    { append_char('\r'); }
<DQUOTES>\\t    { append_char('\t'); }
<DQUOTES>\\b    { append_char('\b'); }
<DQUOTES>\\f    { append_char('\f'); }
<DQUOTES>\\v    { append_char('\v'); }
<DQUOTES>\\\\   { append_char('\\'); }
<DQUOTES>\\\"   { append_char('\"'); }
<DQUOTES>\\\'   { append_char('\''); }
<DQUOTES>\\\?   { append_char('\?'); }
<DQUOTES>\\.    { append_char(yytext[1]); }
<DQUOTES>\\[0-7]{1,3} { append_char((char)strtol(yytext+1, 0, 8));  }
<DQUOTES>\\[xX][0-9a-fA-F]{1,3} { append_char((char)strtol(yytext+2, 0, 16));  }
<DQUOTES>[^\\\"\n]*  { append_str(yytext); }
<DQUOTES>\n     { name_stack->line_no++; yylineno++; } /* track line numbers, but strip new line */


    /* single quoted strings are absolute literals */
\'  {
        bidx = 0;
        memset(buffer, 0, sizeof(buffer));
        BEGIN(SQUOTES);
    }

<SQUOTES>\' {
        strncpy(strbuf, buffer, sizeof(strbuf));
        BEGIN(INITIAL);
        return QSTRG;
    }

<SQUOTES>[^\\'\n]*  { append_str(yytext); }
<SQUOTES>\\.    { append_str(yytext); }
<SQUOTES>\n     { append_str(yytext); name_stack->line_no++; yylineno++; } /* don't strip new lines */

.               { warning("unrecognized character: %c (0x%02X)", yytext[0], yytext[0]);}

<<EOF>> {

        _DEBUG("SCANNER: %s: closing file", name_stack->name);
        _file_name_stack *name = name_stack->next;
        free(name_stack->name);
        free(name_stack);
        name_stack = name;

        memset(strbuf, 0, sizeof(strbuf));
        yypop_buffer_state();
        if(!YY_CURRENT_BUFFER) {
            yyterminate();
        }
        import_depth--;

        //return EOF;
    }

%%

int open_file(const char *fname) {

    _file_name_stack *name;
    char locbuf[1024];

    import_depth++;
    if(import_depth > MAX_IMPORTS) {
        syntax("exceeded maximum import depth (%d), circular imports?", MAX_IMPORTS);
        fatal_error("import error, cannot continue");
    }

    if(find_file(fname, locbuf, sizeof(locbuf)) == NULL) {
        syntax("cannot find the input file: %s", fname);
        return 1;
    }

    _DEBUG("SCANNER: %s: open file", locbuf);
    if(NULL == (name = calloc(1, sizeof(_file_name_stack))))
        fatal_error("cannot allocate memory for file stack");

    if(NULL == (name->name = strdup(locbuf)))
        fatal_error("cannot allocate memory for file stack name");

    name->next = name_stack;
    name->line_no = 1;
    name->col_no = 1;
    name_stack = name;

    yyin = fopen(locbuf, "r");
    if(NULL == yyin) {
        syntax("cannot open the input file: \"%s\": %s", locbuf, strerror(errno));
        return 1;
    }

    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
    return 0;
}

// Tracking and global interface
char *get_file_name(void) {
    if(NULL != name_stack)
        return name_stack->name;
    else
        return "no name";
}

int get_line_number(void) {
    if(NULL != name_stack)
        return name_stack->line_no;
    else
        return -1;
}

int get_col_number(void) {
    if(NULL != name_stack)
        return name_stack->col_no;
    else
        return -1;
}

const char *get_tok_str(void) {
    return strbuf;
}

int get_token(void) {

    memset(strbuf, 0, sizeof(strbuf));
    return yylex();
    //int retv = yylex();
    //if(0 == retv)
    //    memset(strbuf, 0, sizeof(strbuf));
    //
    //return retv;
}
