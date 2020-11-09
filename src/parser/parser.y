%debug
%defines
%locations

%{
//#undef _DEBUGGING
//#undef _TRACE
//#define _TRACE(...)

//#include "../include/common.h"
#include "common.h"

#define TOKSTR get_tok_str()

%}
%define parse.error verbose
%locations

%union {
    int type;
    double fpval;
    int intval;
    char* str;
    int boolean;
    char* symbol;
    char* compound;
}

%token <fpval> FPNUM
%token <intval> INTNUM
%token <str> QSTRG
%token <type> DICT LIST BOOL STRING FLOAT INTEGER
%token <boolean> TRUE FALSE
%token <symbol> SYMBOL
%token <compound> COMPOUND

%type <str> formatted_string any_symbol
%type <type> type_name

%token NOTHING IMPORT CONSTRUCT DESTRUCT DESTROY
%token FOR IF ELSE WHILE DO SWITCH CASE BREAK CONTINUE
%token AND OR NOT EQU NEQU LTEQU GTEQU LESS MORE
%token DEFAULT  ENTRY

    // %right '='
%left AND OR
%left EQU NEQU
%left LESS MORE LTEQU GTEQU
%right ':'
%left '+' '-'
%left '*' '/' '%'
%left NEG
%right NOT '~'

%%
    /*
        Module rules.
     */
module
    : module_list {
        _DEBUG(11, "module finished");
        if(!get_flag(ENTRY_DEFINED))
            warning("no entry point defined for program.");
    }

module_list
    : module_item
    | module_list module_item
    ;

module_item
    : import_definition
    | class_definition
    ;

    /*
        Literal values rules.
    */
// compound_symbol
//     : SYMBOL {
//             _TRACE("new compound symbol name: %s", $1);
//             push_name(TOKSTR);
//         }
//     | compound_symbol '.' SYMBOL {
//             _TRACE("adding to compound name: %s", TOKSTR);
//             add_name(TOKSTR);
//         }
//     | compound_symbol error SYMBOL
//     | compound_symbol '.' error
//     ;

any_symbol
    : COMPOUND {
            _TRACE("compound symbol: %s", $1);
            $$ = $1;
        }
    | SYMBOL {
            _TRACE("simple symbol: %s", $1);
            $$ = $1;
    }
    ;

type_name
    : DICT {
            _TRACE("defining dict data type");
            $$ = $1;
            //push_token($1);
        }
    | LIST {
            _TRACE("defining list data type");
            $$ = $1;
            //push_token($1);
        }
    | BOOL {
            _TRACE("defining boolean data type");
            $$ = $1;
            //push_token($1);
        }
    | STRING {
            _TRACE("defining string data type");
            $$ = $1;
            //push_token($1);
        }
    | FLOAT {
            _TRACE("defining number data type");
            $$ = $1;
            //push_token($1);
        }
    | INTEGER {
            _TRACE("defining number data type");
            $$ = $1;
            //push_token($1);
        }
    | SYMBOL {
            _TRACE("symbol name as a type name");
            $$ = SYMBOL;
            //push_token(SYMBOL);
        }
    | COMPOUND {
            _TRACE("symbol name as a type name");
            $$ = COMPOUND;
            //push_token(COMPOUND);
        }
    // | error
    ;

expression_list
    : expression {
            _TRACE("begin expression list");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    | expression_list ',' expression {
            _TRACE("add expression to list");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    ;

possible_blank_expr_list
    : {
            _TRACE("blank expression list");
        }
    | expression {
            _TRACE("begin expression list");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    | expression_list ',' expression {
            _TRACE("add expression to list");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    ;

formatted_string
    : QSTRG {
            _TRACE("formatted string without external format '%s'", TOKSTR);
        }
    | QSTRG {
            _TRACE("begin formatted string with formtting '%s'", TOKSTR);
        } ':' '(' {
            _TRACE("formatted string parameter list begining");
        } expression_list {
            _TRACE("formatted string parameter list ending");
        } ')' {
            _TRACE("end of formtted string definition");
        }
    // | error
    ;

    /*
        Imports rules
    */
import_definition
    : IMPORT SYMBOL {
            _TRACE("import definition, importing symbol: %s", TOKSTR);
            if(open_file(TOKSTR)) {
                syntax("cannot open input file for import: %s", TOKSTR);
                fatal_error("cannot continue");
            }
            _TRACE("import definition finished");
        }
    | IMPORT error
    ;


    /*
        Class definition related rules.
    */
class_body_item
    : type_assignment ';' {  /* data_definition { */
            _TRACE("class body data with assignment definition completed");
        }
    | data_type_intro ';' {
            _TRACE("class body data definition completed");
        }
    | method_definition {
            _TRACE("class body method definition completed");
        }
    | constructor_definition {
            _TRACE("class body constructor definition completed");
            set_flag(CONSTRUCTOR_DEFINED);
        }
    | destructor_definition {
            _TRACE("class body destructor definition completed");
            set_flag(DESTRUCTOR_DEFINED);
        }
    ;

class_body
    : class_body_item
    | class_body class_body_item
    ;

class_name
    : SYMBOL {
            _TRACE("");
            _TRACE("start class definition");
            _TRACE("class name: %s", TOKSTR);
        }
    | ENTRY {
            _TRACE("");
            _TRACE("start ENTRY class definition");
            if(get_flag(ENTRY_DEFINED))
                syntax("only one entry class may be defined for program");
            set_flag(CLASS_IS_ENTRY);
    }
    ;

class_definition_params
    : class_name '{' {
            _TRACE("start class body");
        }
    | class_name '(' ')' '{' {
            _TRACE("start class body");
        }
    | class_name '(' COMPOUND {
            char buffer[128];
            pop_name(buffer, sizeof(buffer));
            _TRACE("class inherits from %s", $3);
        } ')' '{'
    ;

class_definition
    : class_definition_params class_body '}' {
            _TRACE("end class body and definition");
            char* f = flag_to_str();
            _TRACE("class flags: %s", f);
            FREE(f);
            _TRACE("");
            if(get_flag(CLASS_IS_ENTRY)) {
                clear_flag(CLASS_IS_ENTRY);
                if(!get_flag(CONSTRUCTOR_DEFINED))
                    syntax("entry class must have a constructor defined");
                else
                    set_flag(ENTRY_DEFINED);
            }
            clear_flag(CONSTRUCTOR_DEFINED);
            clear_flag(DESTRUCTOR_DEFINED);
        }
    | error
    ;

    /*
        Data definition rules.
        These definitions are used inside a class as well as a function.
    */
data_type_intro
    : type_name SYMBOL {
            _TRACE("type definition symbol name: %s", $2);
        }
    ;

    /*
        Method definition related rules
    */
method_def_param_list
    : data_type_intro {
            _TRACE("method parameter list (1)");
        }
    | method_def_param_list ',' data_type_intro {
            _TRACE("method parameter list (2)");
        }
    | error
    ;

method_param_def
    :  method_def_param_list {
            _TRACE("complete method parameter list");
        }
    |  /* blank */ {
            _TRACE("empty method parameter list");
        }
    ;

method_definition
    : SYMBOL {
        _TRACE("begin method definition with symbol: %s", $1);
        } '(' method_param_def {
            _TRACE("end of input parameter list, begin of output parameters");
        } ')' '(' method_param_def {
            _TRACE("end of output parameters");
            _TRACE("begin method body definition");
        } ')' method_body {
            _TRACE("end method body definition");
        }
    ;

method_body_element
    : for_clause
    | if_clause
    | while_clause
    | do_clause
    | switch_clause
    | assignment ';'
    | data_type_intro ';'
    | type_assignment ';'
    | function_call ';'
    | destroy_statement ';'
    ;

method_body_element_list
    : method_body_element
    | method_body_element_list method_body_element
    ;

method_body
    : '{' {
            _TRACE("start method body definition");
        } method_body_element_list '}' {
            _TRACE("ending method body definition");
        }
    | '{' '}' {
            _TRACE("empty method body definition");
        }
    ;

constructor_definition
    : CONSTRUCT {
            _TRACE("begin constructor definition");
            _TRACE("begin constructor parameter list");
        } '(' method_param_def {
            _TRACE("end constructor parameter list");
            _TRACE("begin constructor method body");
        } ')'  method_body {
            _TRACE("end construcor method body");
            _TRACE("end construcor method definition");
            set_flag(CONSTRUCTOR_DEFINED);
        }
    | CONSTRUCT error
    ;

destructor_definition
    : DESTRUCT {
            _TRACE("begin destructor definition and body");
        } method_body {
            _TRACE("end destructor definition and body");
            set_flag(DESTRUCTOR_DEFINED);
        }
    | DESTRUCT error
    ;

    /*
        Expression related rules.
    */
    /* subscript_item
    : '[' {
            _TRACE("begin list subscript expression");
        } expression {
            _TRACE("end list subscript expression");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        } ']'
    ;

    subscript_list
    : subscript_item
    | subscript_list subscript_item

    subscripted_compound_name
    : compound_symbol {
            _TRACE("subscripted compound name: %s", get_compound_name());
            destroy_compound_name();
            _TRACE("begin subscripted compound name list");
        } subscript_list {
            _TRACE("end subscripted compound name list");
        }
    ; */

// expression_name
//     : compound_symbol {
//             const char* name = get_compound_name();
//             _TRACE("expression compound name: %s", name);
//             add_expr_symbol(name);
//             destroy_compound_name();
//         }
//     /* | subscripted_compound_name {
//             TODO: Subscripts not supported yet
//             const char* name = get_compound_name(comp_name);
//             _TRACE("expression compound name with subscript");
//             if(!get_flag(PARSING_EXPRESSION)) {
//                 create_expression();
//                 set_flag(PARSING_EXPRESSION);
//             }
//             add_expr_symbol(name);
//             destroy_compound_name(comp_name);
//         } */
//     ;

    /*
     *  Parsing an expression always begins with an expression factor
     *  and ends when the expression is accepted as syntax.
     */
expression_factor
    : FPNUM {
            _TRACE("expression literal float: %g", $1);
            add_expr_float($1);
        }
    | INTNUM {
            _TRACE("expression literal int: %d", $1);
            add_expr_int($1);
        }
    | TRUE {
            add_expr_true();
        }
    | FALSE {
            add_expr_false();
        }
    | formatted_string {
            _TRACE("formatted string expression value");
            add_expr_string($1);
        }
    | any_symbol {
            _TRACE("expression symbol variable value; %s", $1);
            add_expr_symbol($1);
        }
    ;

expression
    : expression_factor {
            _TRACE("expression factor");
        }
    | expression '+' expression {
            _TRACE("expression ADD operator");
            add_expr_operator(EXP_ADD_OPERATOR);
        }
    | expression '-' expression {
            _TRACE("expression SUB operator");
            add_expr_operator(EXP_SUB_OPERATOR);
        }
    | expression '/' expression {
            _TRACE("expression DIV operator");
            add_expr_operator(EXP_DIV_OPERATOR);
        }
    | expression '*' expression {
            _TRACE("expression MUL operator");
            add_expr_operator(EXP_MUL_OPERATOR);
        }
    | expression '%' expression {
            _TRACE("expression MOD operator");
            add_expr_operator(EXP_MOD_OPERATOR);
        }
    | expression AND expression {
            _TRACE("expression AND operator");
            add_expr_operator(EXP_AND_OPERATOR);
        }
    | expression OR expression {
            _TRACE("expression OR operator");
            add_expr_operator(EXP_OR_OPERATOR);
        }
    | expression LESS expression {
            _TRACE("expression LESS operator");
            add_expr_operator(EXP_LT_OPERATOR);
        }
    | expression MORE expression {
            _TRACE("expression MORE operator");
            add_expr_operator(EXP_GT_OPERATOR);
        }
    | expression EQU expression {
            _TRACE("expression EQU operator");
            add_expr_operator(EXP_EQU_OPERATOR);
        }
    | expression NEQU expression {
            _TRACE("expression NEQU operator");
            add_expr_operator(EXP_NEQU_OPERATOR);
        }
    | expression LTEQU expression {
            _TRACE("expression LEQU operator");
            add_expr_operator(EXP_LTE_OPERATOR);
        }
    | expression GTEQU expression {
            _TRACE("expression GEQU operator");
            add_expr_operator(EXP_GTE_OPERATOR);
        }
    | '-' expression %prec NEG {
            _TRACE("expression unary minus");
            add_expr_operator(EXP_UNARY_PLUS);
        }
    | '+' expression %prec NEG {
            _TRACE("expression unary plus");
            add_expr_operator(EXP_UNARY_MINUS);
        }
    | NOT expression {
            _TRACE("expression NOT operator");
            add_expr_operator(EXP_NOT_OPERATOR);
        }
    | type_name ':' expression {
            _TRACE("type of casting expression");
            add_expr_cast($1);
        }
    | '(' expression ')'
    ;

    /*************************************
        Method/function contents rules
    */

    /*
        Function call related rules
    */
call_output_parameter_list
    :
    | any_symbol {
            _TRACE("function call output parameter (1): %s", "not implemented");
        }
        | call_output_parameter_list ',' any_symbol {
            _TRACE("function call output parameter (2): %s", "not implemented");
        }
    ;


function_call
    : any_symbol {
            //char buffer[128];
            //pop_name(buffer, sizeof(buffer));
            _TRACE("function call name: %s", $1);
            _TRACE("begin function call input parameters");
        } '(' possible_blank_expr_list {
            _TRACE("end function call input parameters");
            _TRACE("begin function call output parameters");
        } ')' '(' call_output_parameter_list ')' {
            _TRACE("end function call output parameters");
        }
    ;

destroy_statement
    : DESTROY any_symbol {
            //char buffer[128];
            //pop_name(buffer, sizeof(buffer));
            _TRACE("destroy symbol: %s", $2);
        }
    | DESTROY error ';'
    ;

    /*
        Common rules for branching and defining loop bodies
    */
jump_clause
    : CONTINUE ';' {
            _TRACE("jump clause as continue");
        }
    | BREAK ';' {
            _TRACE("jump clause as break");
        }
    ;

loop_body_element
    : method_body_element
    | jump_clause
    ;

loop_body_element_list
    : loop_body_element
    | loop_body_element_list loop_body_element
    ;

loop_body
    : '{' '}' {
            _TRACE("empty loop body");
        }
    | '{' {
            _TRACE("begin loop body");
        } loop_body_element_list '}' {
            _TRACE("end loop body");
        }
    ;

    /*
        FOR loop related rules
    */
for_initialize
    : type_assignment ';' {
            _TRACE("for loop initialize with type name: %s", TOKSTR);
        }
    | assignment ';' {
            _TRACE("for loop initialize assignment");
    }
    ;

for_arith_expression
    : expression {
            _TRACE("for loop arithmetic assignment clause");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    | assignment {
            _TRACE("for loop generic assignment clause");
        }
    ;

for_clause
    : FOR '(' {
            _TRACE("begin for loop definition");
        } for_initialize expression ';' for_arith_expression {
            _TRACE("begin for loop loop body");
        } ')' loop_body {
            _TRACE("end for loop loop body");
            _TRACE("end for loop definition");
        }
    ;

    /*
        If/else clause related rules
    */
else_clause
    : ELSE '(' {
            _TRACE("begin else clause with expression definition");
            _TRACE("begin else clause expression");
        } expression {
            _TRACE("end else clause expression");
            _TRACE("begin else clause method body");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        } ')' method_body {
            _TRACE("end else clause method body");
            _TRACE("end else clause with expression definition");
        }
    | ELSE {
            _TRACE("begin else clause with no expression definition");
            _TRACE("begin else clause expression");
        } method_body {
            _TRACE("begin else clause expression");
            _TRACE("end else clause with no expression definition");
        }
    ;

else_body
    : else_clause
    | else_body else_clause
    | method_body
    | error
    ;

if_clause
    : IF '(' {
            _TRACE("begin if clause definition");
            _TRACE("begin if clause branch expression definition");
        } expression {
            _TRACE("end if clause branch expression definition");
            _TRACE("begin else clause definition");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        } ')' else_body {
            _TRACE("end else clause definition");
            _TRACE("end if clause definition");
        }
    ;

    /*
        While clause rules.
    */
while_clause
    : WHILE '(' {
            _TRACE("begin while clause with expression definition");
            _TRACE("begin while clause branch expression definition");
        } expression {
            _TRACE("end while clause branch expression definition");
            _TRACE("begin while clause loop body definition");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        } ')' loop_body {
            _TRACE("end while clause loop body definition");
            _TRACE("end while clause with expression definition");
        }
    | WHILE {
            _TRACE("begin while clause with no expression definition");
            _TRACE("begin while clause loop body definition");
        } loop_body {
            _TRACE("");
        }
    ;

do_clause
    : DO {
            _TRACE("begin do/while clause definition");
            _TRACE("begin do/while clause loop body definition");
        } loop_body {
            _TRACE("end do/while clause loop body definition");
        } WHILE '(' {
            _TRACE("begin do/while branch expression definition");
        } expression ')' ';' {
            _TRACE("end do/while branch expression definition");
            _TRACE("end do/while clause definition");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    ;

    /*
        Switch/case related rules
    */
case_clause
    : CASE INTNUM {
            _TRACE("begin case clause and loop body: %s", TOKSTR);
        } loop_body {
            _TRACE("end case loop body and clause");
        }
    | CASE error
    ;

default_case
    : DEFAULT {
            _TRACE("begin default case clause and loop body");
        } loop_body {
            _TRACE("end default case clause and loop body");
        }
    | DEFAULT error
    ;

case_body
    : case_clause
    | case_body case_clause
    ;

switch_clause_intro
    : SWITCH '(' {
            _TRACE("begin switch/case clause");
            _TRACE("begin switch/case expression");
        } expression ')' '{' {
            _TRACE("end switch/case expression");
            _TRACE("begin switch/case body");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        } case_body {
            _TRACE("end switch/case body");
            _TRACE("end switch/case clause");
        }
    ;

switch_clause
    : switch_clause_intro '}' {
            _TRACE("switch/case clause with no default clause");
        }
    | switch_clause_intro default_case '}' {
            _TRACE("switch/case clause with default clause");
        }
    ;

    /*
        Assignment related rules
    */
assignment_target
    : expression {
            _TRACE("assignment target is an expression");
            validate_expression();
            destroy_expression();
            clear_flag(PARSING_EXPRESSION);
        }
    | NOTHING {
            _TRACE("assignment target is nothing");
        }
    ;

assignment
    : any_symbol {
            //char buffer[128];
            //pop_name(buffer, sizeof(buffer));
            _TRACE("assignment to name: %s", $1);
        } '=' assignment_target {
            _TRACE("end assignment statement");
        }
    ;

type_assignment
    : type_name SYMBOL {
            _TRACE("type assignment of type: %d to %s", $1, $2);
        } '=' assignment_target {
            _TRACE("after type assignment");
        }
    ;


%%

#include <stdio.h>

extern char yytext[];

void yyerror(const char* s)
{
	fflush(stdout);
	fprintf(stdout, "%s: line %d: at %d: %s: %s\n", get_file_name(), get_line_number(), get_col_number(), s);
    inc_error_count();
}
