%debug
%defines
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

#define TOKSTR get_tok_str()

%}
%define parse.error verbose
%locations

%token NOTHING IMPORT CLASS METHOD CREATE DESTROY
%token DICT LIST BOOL TRUE FALSE STRING NUM FOR
%token IF ELSE WHILE DO SWITCH CASE BREAK CONTINUE
%token DEFAULT SYMBOL NUMBER QSTRG
%token AND OR NOT EQU NEQU LTEQU GTEQU LESS MORE


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
module
    : module_list {}
    ;

module_item
    : import_definition {}
    | class_definition {}
    ;

module_list
    : module_item {}
    | module module_item {}
    ;

    /*
        Literal values rules.
    */
complex_name
    : SYMBOL {}
    | complex_name '.' SYMBOL {}
    ;

intrinsic_type
    : DICT {}
    | LIST {}
    | BOOL {}
    | STRING {}
    | NUM {}
    | complex_name {}
    ;

formatted_string_param
    : QSTRG {}
    | expression {}
    ;

formatted_string_param_list
    : formatted_string_param {}
    | formatted_string_param_list ',' formatted_string_param {}
    ;

formatted_string
    : QSTRG {}
    | QSTRG {} ':' '(' {} formatted_string_param_list {} ')'
    ;

bool_value
    : TRUE {}
    | FALSE {}
    ;

    /*
        Imports rules
    */
import_definition
    : IMPORT SYMBOL {} ';' {}
    ;

    /*
        Class definition related rules.
    */
class_body_item
    : class_data_definition {}
    | method_definition {}
    | constructor_definition {}
    | destructor_definition {}
    ;

class_body
    : class_body_item {}
    | class_body class_body_item {}
    ;

class_definition
    : CLASS {} SYMBOL {} '(' ')' '{' {} class_body {} '}'
    ;

    /*
        Data definition rules.
    */
class_data_definition
    : intrinsic_type {} SYMBOL {} ';' {}
    ;

function_data_definition_target
    : NOTHING {}
    | expression {}
    | type_cast {} expression {}
    | formatted_string {}
    ;

function_data_definition_symbol
    : SYMBOL {}
    ;

function_data_definition
    : intrinsic_type function_data_definition_symbol ';' {}
    | intrinsic_type function_data_definition_symbol '=' {} function_data_definition_target ';' {}
    ;

    /*
        Method definition related rules
    */
method_def_param
    : intrinsic_type {} SYMBOL {}
    ;

method_def_param_list
    : method_def_param {}
    | method_def_param_list ',' method_def_param {}
    ;

method_param_def
    :  method_def_param_list {}
    |  /* blank */ {}
    ;

method_definition
    : METHOD {} SYMBOL {} '(' {} method_param_def {} ')' '(' {} method_param_def {} ')' {} method_body {}
    ;

method_body_element
    : function_data_definition {}
    | function_call {}
    | for_clause {}
    | if_clause {}
    | while_clause {}
    | do_clause {}
    | switch_clause {}
    | assignment ';' {}
    ;

method_body_element_list
    : method_body_element {}
    | method_body_element_list method_body_element {}
    ;

method_body
    : '{' {} method_body_element_list {} '}' {}
    | '{' '}' {}
    ;

constructor_definition
    : CREATE {} '(' {} method_param_def {} ')' {} method_body {}
    ;

destructor_definition
    : DESTROY {} method_body {}
    ;

    /*
        Expression related rules.
    */
subscript_item
    : '[' {} expression {} ']'
    | '[' {} formatted_string {} ']'
    ;

subscript_list
    : subscript_item {}
    | subscript_list subscript_item {}

expression_name
    : complex_name {}
    | complex_name {} subscript_list {}
    ;

expression
    : NUMBER {}
    | expression_name {}
    | expression '+' expression {}
    | expression '-' expression {}
    | expression '/' expression {}
    | expression '*' expression {}
    | expression '%' expression {}
    | expression AND expression {}
    | expression OR expression {}
    | expression LESS expression {}
    | expression MORE expression {}
    | expression EQU expression {}
    | expression NEQU expression {}
    | expression LTEQU expression {}
    | expression GTEQU expression {}
    | '-' expression %prec NEG {}
    | NOT expression {}
    | '(' expression ')'
    ;

    /*************************************
        Method/function contents rules
    */

    /*
        Function call related rules
    */
function_call_parameter
    : formatted_string {}
    | expression {}
    ;

function_call_parameter_list
    :
    | function_call_parameter {}
    | function_call_parameter_list ',' function_call_parameter {}
    ;

function_call
    : complex_name {} '(' {} function_call_parameter_list {} ')' '(' {} function_call_parameter_list {} ')' ';' {}
    | DESTROY complex_name {} ';' {}
    ;

    /*
        Common rules for branching and defining loop bodies
    */
branch_expression
    : expression {}
    | bool_value {}
    ;


jump_clause
    : CONTINUE ';' {}
    | BREAK ';' {}
    ;

loop_body_element
    : method_body_element {}
    | jump_clause {}
    ;

loop_body_element_list
    : loop_body_element {}
    | loop_body_element_list loop_body_element {}
    ;

loop_body
    : '{' '}' {}
    | '{' {} loop_body_element_list {} '}' {}
    ;

    /*
        For loop related rules
    */
for_initialize_assign
    : NOTHING {}
    | expression {}
    | bool_value {}
    ;

for_initialize
    : intrinsic_type {} SYMBOL {} '=' for_initialize_assign ';' {}
    | assignment {} ';' {}
    ;


for_test_expression
    : expression {} ';' {}
    ;

for_arith_expression
    : expression {}
    | assignment {}
    ;

for_clause
    : FOR '(' {} for_initialize for_test_expression  for_arith_expression {} ')' loop_body {}
    ;

    /*
        If/else clause related rules
    */
else_clause
    : ELSE '(' {} expression {} ')' method_body {}
    | ELSE {} method_body {}
    ;

else_body
    : else_clause {}
    | else_body else_clause {}
    | method_body {}
    ;

if_clause
    : IF '(' {} branch_expression {} ')' else_body {}
    ;

    /*
        While clause rules.
    */
while_clause
    : WHILE '(' {} branch_expression {} ')' loop_body {}
    ;

do_clause
    : DO {} loop_body {} WHILE '(' {} branch_expression {} ')' ';' {}
    ;

    /*
        Switch/case related rules
    */
case_clause
    : CASE NUMBER {} loop_body {}
    ;

default_case
    : DEFAULT {} loop_body {}
    ;

case_body
    : case_clause {}
    | case_body case_clause {}
    ;

switch_clause_intro
    : SWITCH '(' {} expression {} ')' '{' {} case_body {}
    ;

switch_clause
    : switch_clause_intro '}' {}
    | switch_clause_intro default_case {} '}' {}
    ;

    /*
        Assignment related rules
    */
type_cast
    : intrinsic_type {} ':' {}
    ;

assignment_target
    : expression {}
    | formatted_string {}
    | type_cast expression {}
    | NOTHING {}
    | bool_value {}
    ;

assignment
    : complex_name {} '=' assignment_target {}
    ;

%%

#include <stdio.h>

extern char yytext[];

void yyerror(const char* s)
{
	fflush(stdout);
	fprintf(stdout, "\n%s: line %d: at %d: %s\n\n", get_file_name(), get_line_number(), get_col_number(), s);
    //inc_error_count();
}
