%debug
%defines
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#undef _DEBUGGING
#include "../include/scanner.h"
#include "../include/errors.h"

#define TOKSTR get_tok_str()

%}
%define parse.error verbose
%locations

%token NOTHING IMPORT CLASS METHOD CONSTRUCT DESTRUCT DESTROY
%token DICT LIST BOOL TRUE FALSE STRING NUM FOR
%token IF ELSE WHILE DO SWITCH CASE BREAK CONTINUE
%token DEFAULT SYMBOL NUMBER QSTRG
%token AND OR NOT EQU NEQU LTEQU GTEQU LESS MORE

%left '='
%left AND OR
%left EQU NEQU
%left LESS MORE LTEQU GTEQU
%left '+' '-'
%left '*' '/' '%'
%left NEG
%right NOT '~'

%%
    /*
        Module rules.
     */
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
compound_name
    : SYMBOL {
            _TRACE("new symbol name: %s", TOKSTR);
        }
    | compound_name '.' SYMBOL {
            _TRACE("adding to compound name: %s", TOKSTR);
        }
    | compound_name error SYMBOL
    | compound_name '.' error
    ;

type_name
    : DICT {
            _TRACE("defining dict data type");
        }
    | LIST {
            _TRACE("defining list data type");
        }
    | BOOL {
            _TRACE("defining boolean data type");
        }
    | STRING {
            _TRACE("defining string data type");
        }
    | NUMBER {
            _TRACE("defining number data type");
        }
    | compound_name {
            _TRACE("compound name as a type name seen");
        }
    | error
    ;

formatted_string_param
    : QSTRG {
            _TRACE("quoted string as formatted string parameter");
        }
    | expression {
            _TRACE("expression as formatted string parameter");
        }
    | error
    ;

formatted_string_param_list
    : formatted_string_param {
            _TRACE("adding formatted string parameter (1)");
        }
    | formatted_string_param_list ',' formatted_string_param {
            _TRACE("adding formatted string parameter (2)");
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
        } formatted_string_param_list {
            _TRACE("formatted string parameter list ending");
        } ')' {
            _TRACE("end of formtted string definition");
        }
    | error
    ;

bool_value
    : TRUE {
            _TRACE("boolean value: true");
        }
    | FALSE {
            _TRACE("boolean value: false");
        }
    ;

    /*
        Imports rules
    */
import_definition
    : IMPORT SYMBOL {
            _TRACE("import definition, importing symbol: %s", TOKSTR);
        } ';' {
            _TRACE("import definition finished");
        }
    | IMPORT error ';'
    ;


    /*
        Class definition related rules.
    */
class_body_item
    : data_definition {
            _TRACE("class body data definition completed");
        }
    | method_definition {
            _TRACE("class body method definition completed");
        }
    | constructor_definition {
            _TRACE("class body constructor definition completed");
        }
    | destructor_definition {
            _TRACE("class body destructor definition completed");
        }
    ;

class_body
    : class_body_item
    | class_body class_body_item
    ;

class_name
    : CLASS {
            _TRACE("");
            _TRACE("start class definition");
        } SYMBOL {
            _TRACE("class name: %s", TOKSTR);
        }
    ;

class_definition
    : class_name '(' ')' '{' {
            _TRACE("start class body");
        } class_body '}' {
            _TRACE("end class body and definition");
            _TRACE("");
        }
    | class_name '(' compound_name {
            _TRACE("class inherits from %s", "not implemented");
        } ')' '{' {
            _TRACE("start class body");
        } class_body '}' {
            _TRACE("end class body and definition");
            _TRACE("");
        }
    | error
    ;

    /*
        Data definition rules.
        These definitions are used inside a class as well as a function.
    */
data_type_intro
    : type_name SYMBOL {
            _TRACE("type definition symbol name: %s", TOKSTR);
        }
    ;

data_definition
    : data_type_intro ';' {
            _TRACE("end of data definition without assignment");
        }
    | data_type_intro '=' {
            _TRACE("start of data definition with assignment");
        } assignment_target {
            _TRACE("end of data definition with assignment");
        } ';'
    | error ';'
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
    : METHOD SYMBOL {
        } '(' method_param_def {
            _TRACE("begin method definition with symbol: %s", TOKSTR);
            _TRACE("begin of input parameter list");
        } ')' '(' method_param_def {
            _TRACE("end of input parameter list and begin output parameters");
            _TRACE("begin method body definition");
        } ')' method_body {
            _TRACE("end method body definition");
        }
    | METHOD error
    ;

method_body_element
    : data_definition
    | function_call
    | for_clause
    | if_clause
    | while_clause
    | do_clause
    | switch_clause
    | assignment ';'
    | destroy_statement
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
        }
    | CONSTRUCT error
    ;

destructor_definition
    : DESTRUCT {
            _TRACE("begin destructor definition and body");
        } method_body {
            _TRACE("end destructor definition and body");
        }
    | DESTRUCT error
    ;

    /*
        Expression related rules.
    */
subscript_item
    : '[' {
            _TRACE("begin list subscript expression");
        } expression {
            _TRACE("end list subscript expression");
        } ']'
    | '[' {
            _TRACE("begin dict subscript definition");
        } formatted_string {
            _TRACE("end dict subscript definition");
        } ']'
    ;

subscript_list
    : subscript_item
    | subscript_list subscript_item

expression_name
    : compound_name {
            _TRACE("expression compound name: %s", "not supported");
        }
    | compound_name {
            _TRACE("expression compound name with subscript");
            _TRACE("begin expression subscript definition");
        } subscript_list {
            _TRACE("end expression subscript definition");
        }
    ;

expression
    : NUM {
            _TRACE("expression literal number: %s", TOKSTR);
        }
    | expression_name {
            _TRACE("expression variable value");
        }
    | expression '+' expression {
            _TRACE("expression ADD operator");
        }
    | expression '-' expression {
            _TRACE("expression SUB operator");
        }
    | expression '/' expression {
            _TRACE("expression DIV operator");
        }
    | expression '*' expression {
            _TRACE("expression MUL operator");
        }
    | expression '%' expression {
            _TRACE("expression MOD operator");
        }
    | expression AND expression {
            _TRACE("expression AND operator");
        }
    | expression OR expression {
            _TRACE("expression OR operator");
        }
    | expression LESS expression {
            _TRACE("expression LESS operator");
        }
    | expression MORE expression {
            _TRACE("expression MORE operator");
        }
    | expression EQU expression {
            _TRACE("expression EQU operator");
        }
    | expression NEQU expression {
            _TRACE("expression NEQU operator");
        }
    | expression LTEQU expression {
            _TRACE("expression LEQU operator");
        }
    | expression GTEQU expression {
            _TRACE("expression GEQU operator");
        }
    | '-' expression %prec NEG {
            _TRACE("expression unary minus");
        }
    | '+' expression %prec NEG {
            _TRACE("expression unary plus");
        }
    | NOT expression {
            _TRACE("expression NOT operator");
        }
    | '(' expression ')'
    ;

    /*************************************
        Method/function contents rules
    */

    /*
        Function call related rules
    */
function_call_parameter
    : formatted_string {
            _TRACE("function call parameter is formatted string");
        }
    | expression {
            _TRACE("function call parameter is expression");
        }
    ;

function_call_parameter_list
    :
    | function_call_parameter
    | function_call_parameter_list ',' function_call_parameter
    ;

function_call
    : compound_name {
            _TRACE("function call name: %s", "not implemented");
            _TRACE("begin function call input parameters");
        } '(' function_call_parameter_list {
            _TRACE("end function call input parameters");
            _TRACE("begin function call output parameters");
        } ')' '(' function_call_parameter_list ')' ';' {
            _TRACE("end function call output parameters");
        }
    ;

destroy_statement
    : DESTROY compound_name ';' {
            _TRACE("destroy symbol: %s", "not implemented");
        }
    | DESTROY error ';'
    ;

    /*
        Common rules for branching and defining loop bodies
    */
branch_expression
    : expression {
            _TRACE("branch expression as expression");
        }
    | bool_value {
            _TRACE("branch expression as bool value");
        }
    ;

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
        For loop related rules
    */
for_initialize_assign
    : NOTHING {
            _TRACE("for loop initialize assignment to NOTHING");
        }
    | expression {
            _TRACE("for loop initialize assignment with expression");
        }
    | bool_value {
            _TRACE("for loop initialize assignment with bool value");
        }
    ;

for_initialize
    : type_name {
            _TRACE("for loop initialize with type name: %s", TOKSTR);
        } SYMBOL {
            _TRACE("for loop initialize symbol: %s", TOKSTR);
        } '=' for_initialize_assign ';' {
            _TRACE("for loop initialize assignment");
        }
    | assignment ';' {
            _TRACE("for loop initialize simple assignment");
        }
    ;


for_test_expression
    : expression ';' {
            _TRACE("for loop test expression");
        }
    ;

for_arith_expression
    : expression {
            _TRACE("for loop arithmetic assignment clause");
        }
    | assignment {
            _TRACE("for loop generic assignment clause");
        }
    ;

for_clause
    : FOR '(' {
            _TRACE("begin for loop definition");
        } for_initialize for_test_expression  for_arith_expression {
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
        } branch_expression {
            _TRACE("end if clause branch expression definition");
            _TRACE("begin else clause definition");
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
        } branch_expression {
            _TRACE("end while clause branch expression definition");
            _TRACE("begin while clause loop body definition");
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
        } branch_expression ')' ';' {
            _TRACE("end do/while branch expression definition");
            _TRACE("end do/while clause definition");
        }
    ;

    /*
        Switch/case related rules
    */
case_clause
    : CASE NUM {
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
type_cast
    : type_name ':' {
            _TRACE("cast prefux to type: %s", TOKSTR);
        }
    ;

assignment_target
    : expression {
            _TRACE("assignment target is an expression");
        }
    | formatted_string {
            _TRACE("assignment target is a string");
        }
    | type_cast expression {
            _TRACE("assignment target is an expression with a type cast");
        }
    | NOTHING {
            _TRACE("assignment target is nothing");
        }
    | bool_value {
            _TRACE("assignemnt target is bool value");
        }
    ;

assignment
    : compound_name {
            _TRACE("assignment to compound name: %s", "not implemented");
        } '=' assignment_target {
            _TRACE("end assignment statement");
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
