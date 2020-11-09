
%{
#undef _DEBUGGING
//#undef _TRACE
//#define _TRACE(...)

#include "parser.h"
#include "common.h"

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
SYMCH   [a-zA-Z_$@%^&~?|]
SYMBOL  ({SYMCH}+({SYMCH}{DIGIT})*)

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
"string"        { yylval.type = STRING; return STRING; }
"float"         { yylval.type = FLOAT; return FLOAT; }
"int"           { yylval.type = INTEGER; return INTEGER; }
"integer"       { yylval.type = INTEGER; return INTEGER; }
"dict"          { yylval.type = DICT; return DICT; }
"list"          { yylval.type = LIST; return LIST; }
"bool"          { yylval.type = BOOL; return BOOL; }
"true"          { yylval.boolean = 1; return TRUE; }
"True"          { yylval.boolean = 1; return TRUE; }
"TRUE"          { yylval.boolean = 1; return TRUE; }
"false"         { yylval.boolean = 0; return FALSE; }
"False"         { yylval.boolean = 0; return FALSE; }
"FALSE"         { yylval.boolean = 0; return FALSE; }

"nothing"       { return NOTHING; }
"nil"           { return NOTHING; }
"NULL"          { return NOTHING; }
"null"          { return NOTHING; }
"Null"          { return NOTHING; }
"import"        { return IMPORT; }
"constructor"   { return CONSTRUCT; }
"construct"     { return CONSTRUCT; }
"destructor"    { return DESTRUCT; }
"destroy"       { return DESTROY; }

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
"!"             { return NOT; }
"equ"           { return EQU; }
"=="            { return EQU; }
"neq"           { return NEQU; }
"!="            { return NEQU; }
"<>"            { return NEQU; }
"leq"           { return LTEQU; }
"<="            { return LTEQU; }
"geq"           { return GTEQU; }
">="            { return GTEQU; }
"lt"            { return LESS; }
"<"             { return LESS; }
"gt"            { return MORE; }
">"             { return MORE; }

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

    /* A compound symbol has a dot in it. */
({SYMBOL}\.{SYMBOL})+(\.{SYMBOL})* {
        _TRACE("SCANNER: compound symbol scan: %s",yytext);
        //strncpy(strbuf, yytext, sizeof(strbuf));
        yylval.compound = STRDUP(yytext);
        return COMPOUND;
    }

    /* A simple symbol has no dot in it. */
{SYMBOL} {
        _TRACE("SCANNER: symbol scan: %s",yytext);
        //strncpy(strbuf, yytext, sizeof(strbuf));
        yylval.symbol = STRDUP(yytext);
        return SYMBOL;
    }

    /* recognize and ignore comments */
"#*" { BEGIN(COMMENT); _TRACE("SCANNER: start multi-line comment"); }
<COMMENT>"*#" { BEGIN(INITIAL); _TRACE("SCANNER: end multi-line comment"); }
<COMMENT>\n { name_stack->line_no++; yylineno++; }
<COMMENT>.  {}  /* eat everything in between */

    /* eat up until the newline */
"#".* {
        _TRACE("SCANNER: single-line comment");
    }

[0-9]+ {
        _TRACE("SCANNER: INTEGER scanned: %s", yytext);
        //strncpy(strbuf, yytext, sizeof(strbuf));
        yylval.intval = strtoll(yytext, NULL, 10);
        return INTNUM;
    }

    /* recognize a float */
    /*[-+]?[0-9]+\.[0-9]+([eE]*[-+]?[0-9]+)? { */
[0-9]+(\.[0-9]+([eE]+[-+]?[0-9]+)?)? {
        _TRACE("SCANNER: FLOAT scanned: %s", yytext);
        //strncpy(strbuf, yytext, sizeof(strbuf));
        yylval.fpval = strtod(yytext, NULL);
        return FPNUM;
    }


    /* double quoted strings have escapes managed */
\"  {
        bidx = 0;
        memset(buffer, 0, sizeof(buffer));
        BEGIN(DQUOTES);
    }

<DQUOTES>\" {
        //strncpy(strbuf, buffer, sizeof(strbuf));
        yylval.str = STRDUP(buffer);
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
        //strncpy(strbuf, buffer, sizeof(strbuf));
        yylval.str = STRDUP(buffer);
        BEGIN(INITIAL);
        return QSTRG;
    }

<SQUOTES>[^\\'\n]*  { append_str(yytext); }
<SQUOTES>\\.    { append_str(yytext); }
<SQUOTES>\n     { append_str(yytext); name_stack->line_no++; yylineno++; } /* don't strip new lines */

.               { warning("unrecognized character: %c (0x%02X)", yytext[0], yytext[0]);}

<<EOF>> {

        _DEBUG(10, "SCANNER: %s: closing file", name_stack->name);
        _file_name_stack *name = name_stack->next;
        FREE(name_stack->name);
        FREE(name_stack);
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

    _DEBUG(10, "SCANNER: %s: open file", locbuf);
    if(NULL == (name = CALLOC(1, sizeof(_file_name_stack))))
        fatal_error("cannot allocate memory for file stack");

    if(NULL == (name->name = STRDUP(locbuf)))
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
    _DEBUG(10, "strbuf value: %s", strbuf);
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
