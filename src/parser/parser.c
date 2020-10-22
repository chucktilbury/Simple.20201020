/* A Bison parser, made by GNU Bison 3.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/scanner.h"
#include "../include/errors.h"

#define TOKSTR get_tok_str()


#line 83 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NOTHING = 258,                 /* NOTHING  */
    IMPORT = 259,                  /* IMPORT  */
    CLASS = 260,                   /* CLASS  */
    METHOD = 261,                  /* METHOD  */
    CREATE = 262,                  /* CREATE  */
    DESTROY = 263,                 /* DESTROY  */
    DICT = 264,                    /* DICT  */
    LIST = 265,                    /* LIST  */
    BOOL = 266,                    /* BOOL  */
    TRUE = 267,                    /* TRUE  */
    FALSE = 268,                   /* FALSE  */
    STRING = 269,                  /* STRING  */
    NUM = 270,                     /* NUM  */
    FOR = 271,                     /* FOR  */
    IF = 272,                      /* IF  */
    ELSE = 273,                    /* ELSE  */
    WHILE = 274,                   /* WHILE  */
    DO = 275,                      /* DO  */
    SWITCH = 276,                  /* SWITCH  */
    CASE = 277,                    /* CASE  */
    BREAK = 278,                   /* BREAK  */
    CONTINUE = 279,                /* CONTINUE  */
    DEFAULT = 280,                 /* DEFAULT  */
    SYMBOL = 281,                  /* SYMBOL  */
    NUMBER = 282,                  /* NUMBER  */
    QSTRG = 283,                   /* QSTRG  */
    AND = 284,                     /* AND  */
    OR = 285,                      /* OR  */
    NOT = 286,                     /* NOT  */
    EQU = 287,                     /* EQU  */
    NEQU = 288,                    /* NEQU  */
    LTEQU = 289,                   /* LTEQU  */
    GTEQU = 290,                   /* GTEQU  */
    LESS = 291,                    /* LESS  */
    MORE = 292,                    /* MORE  */
    NEG = 293                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NOTHING = 3,                    /* NOTHING  */
  YYSYMBOL_IMPORT = 4,                     /* IMPORT  */
  YYSYMBOL_CLASS = 5,                      /* CLASS  */
  YYSYMBOL_METHOD = 6,                     /* METHOD  */
  YYSYMBOL_CREATE = 7,                     /* CREATE  */
  YYSYMBOL_DESTROY = 8,                    /* DESTROY  */
  YYSYMBOL_DICT = 9,                       /* DICT  */
  YYSYMBOL_LIST = 10,                      /* LIST  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_TRUE = 12,                      /* TRUE  */
  YYSYMBOL_FALSE = 13,                     /* FALSE  */
  YYSYMBOL_STRING = 14,                    /* STRING  */
  YYSYMBOL_NUM = 15,                       /* NUM  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_SWITCH = 21,                    /* SWITCH  */
  YYSYMBOL_CASE = 22,                      /* CASE  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 24,                  /* CONTINUE  */
  YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
  YYSYMBOL_SYMBOL = 26,                    /* SYMBOL  */
  YYSYMBOL_NUMBER = 27,                    /* NUMBER  */
  YYSYMBOL_QSTRG = 28,                     /* QSTRG  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_EQU = 32,                       /* EQU  */
  YYSYMBOL_NEQU = 33,                      /* NEQU  */
  YYSYMBOL_LTEQU = 34,                     /* LTEQU  */
  YYSYMBOL_GTEQU = 35,                     /* GTEQU  */
  YYSYMBOL_LESS = 36,                      /* LESS  */
  YYSYMBOL_MORE = 37,                      /* MORE  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* '%'  */
  YYSYMBOL_NEG = 43,                       /* NEG  */
  YYSYMBOL_44_ = 44,                       /* '~'  */
  YYSYMBOL_45_ = 45,                       /* '.'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_50_ = 50,                       /* ';'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* '='  */
  YYSYMBOL_54_ = 54,                       /* '['  */
  YYSYMBOL_55_ = 55,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_module = 57,                    /* module  */
  YYSYMBOL_module_item = 58,               /* module_item  */
  YYSYMBOL_module_list = 59,               /* module_list  */
  YYSYMBOL_complex_name = 60,              /* complex_name  */
  YYSYMBOL_intrinsic_type = 61,            /* intrinsic_type  */
  YYSYMBOL_formatted_string_param = 62,    /* formatted_string_param  */
  YYSYMBOL_formatted_string_param_list = 63, /* formatted_string_param_list  */
  YYSYMBOL_formatted_string = 64,          /* formatted_string  */
  YYSYMBOL_65_1 = 65,                      /* $@1  */
  YYSYMBOL_66_2 = 66,                      /* $@2  */
  YYSYMBOL_67_3 = 67,                      /* $@3  */
  YYSYMBOL_bool_value = 68,                /* bool_value  */
  YYSYMBOL_import_definition = 69,         /* import_definition  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_class_body_item = 71,           /* class_body_item  */
  YYSYMBOL_class_body = 72,                /* class_body  */
  YYSYMBOL_class_definition = 73,          /* class_definition  */
  YYSYMBOL_74_5 = 74,                      /* $@5  */
  YYSYMBOL_75_6 = 75,                      /* $@6  */
  YYSYMBOL_76_7 = 76,                      /* $@7  */
  YYSYMBOL_77_8 = 77,                      /* $@8  */
  YYSYMBOL_class_data_definition = 78,     /* class_data_definition  */
  YYSYMBOL_79_9 = 79,                      /* $@9  */
  YYSYMBOL_80_10 = 80,                     /* $@10  */
  YYSYMBOL_function_data_definition_target = 81, /* function_data_definition_target  */
  YYSYMBOL_82_11 = 82,                     /* $@11  */
  YYSYMBOL_function_data_definition_symbol = 83, /* function_data_definition_symbol  */
  YYSYMBOL_function_data_definition = 84,  /* function_data_definition  */
  YYSYMBOL_85_12 = 85,                     /* $@12  */
  YYSYMBOL_method_def_param = 86,          /* method_def_param  */
  YYSYMBOL_87_13 = 87,                     /* $@13  */
  YYSYMBOL_method_def_param_list = 88,     /* method_def_param_list  */
  YYSYMBOL_method_param_def = 89,          /* method_param_def  */
  YYSYMBOL_method_definition = 90,         /* method_definition  */
  YYSYMBOL_91_14 = 91,                     /* $@14  */
  YYSYMBOL_92_15 = 92,                     /* $@15  */
  YYSYMBOL_93_16 = 93,                     /* $@16  */
  YYSYMBOL_94_17 = 94,                     /* $@17  */
  YYSYMBOL_95_18 = 95,                     /* $@18  */
  YYSYMBOL_96_19 = 96,                     /* $@19  */
  YYSYMBOL_97_20 = 97,                     /* $@20  */
  YYSYMBOL_method_body_element = 98,       /* method_body_element  */
  YYSYMBOL_method_body_element_list = 99,  /* method_body_element_list  */
  YYSYMBOL_method_body = 100,              /* method_body  */
  YYSYMBOL_101_21 = 101,                   /* $@21  */
  YYSYMBOL_102_22 = 102,                   /* $@22  */
  YYSYMBOL_constructor_definition = 103,   /* constructor_definition  */
  YYSYMBOL_104_23 = 104,                   /* $@23  */
  YYSYMBOL_105_24 = 105,                   /* $@24  */
  YYSYMBOL_106_25 = 106,                   /* $@25  */
  YYSYMBOL_107_26 = 107,                   /* $@26  */
  YYSYMBOL_destructor_definition = 108,    /* destructor_definition  */
  YYSYMBOL_109_27 = 109,                   /* $@27  */
  YYSYMBOL_subscript_item = 110,           /* subscript_item  */
  YYSYMBOL_111_28 = 111,                   /* $@28  */
  YYSYMBOL_112_29 = 112,                   /* $@29  */
  YYSYMBOL_113_30 = 113,                   /* $@30  */
  YYSYMBOL_114_31 = 114,                   /* $@31  */
  YYSYMBOL_subscript_list = 115,           /* subscript_list  */
  YYSYMBOL_expression_name = 116,          /* expression_name  */
  YYSYMBOL_117_32 = 117,                   /* $@32  */
  YYSYMBOL_expression = 118,               /* expression  */
  YYSYMBOL_function_call_parameter = 119,  /* function_call_parameter  */
  YYSYMBOL_function_call_parameter_list = 120, /* function_call_parameter_list  */
  YYSYMBOL_function_call = 121,            /* function_call  */
  YYSYMBOL_122_33 = 122,                   /* $@33  */
  YYSYMBOL_123_34 = 123,                   /* $@34  */
  YYSYMBOL_124_35 = 124,                   /* $@35  */
  YYSYMBOL_125_36 = 125,                   /* $@36  */
  YYSYMBOL_126_37 = 126,                   /* $@37  */
  YYSYMBOL_127_38 = 127,                   /* $@38  */
  YYSYMBOL_branch_expression = 128,        /* branch_expression  */
  YYSYMBOL_jump_clause = 129,              /* jump_clause  */
  YYSYMBOL_loop_body_element = 130,        /* loop_body_element  */
  YYSYMBOL_loop_body_element_list = 131,   /* loop_body_element_list  */
  YYSYMBOL_loop_body = 132,                /* loop_body  */
  YYSYMBOL_133_39 = 133,                   /* $@39  */
  YYSYMBOL_134_40 = 134,                   /* $@40  */
  YYSYMBOL_for_initialize_assign = 135,    /* for_initialize_assign  */
  YYSYMBOL_for_initialize = 136,           /* for_initialize  */
  YYSYMBOL_137_41 = 137,                   /* $@41  */
  YYSYMBOL_138_42 = 138,                   /* $@42  */
  YYSYMBOL_139_43 = 139,                   /* $@43  */
  YYSYMBOL_for_test_expression = 140,      /* for_test_expression  */
  YYSYMBOL_141_44 = 141,                   /* $@44  */
  YYSYMBOL_for_arith_expression = 142,     /* for_arith_expression  */
  YYSYMBOL_for_clause = 143,               /* for_clause  */
  YYSYMBOL_144_45 = 144,                   /* $@45  */
  YYSYMBOL_145_46 = 145,                   /* $@46  */
  YYSYMBOL_else_clause = 146,              /* else_clause  */
  YYSYMBOL_147_47 = 147,                   /* $@47  */
  YYSYMBOL_148_48 = 148,                   /* $@48  */
  YYSYMBOL_149_49 = 149,                   /* $@49  */
  YYSYMBOL_else_body = 150,                /* else_body  */
  YYSYMBOL_if_clause = 151,                /* if_clause  */
  YYSYMBOL_152_50 = 152,                   /* $@50  */
  YYSYMBOL_153_51 = 153,                   /* $@51  */
  YYSYMBOL_while_clause = 154,             /* while_clause  */
  YYSYMBOL_155_52 = 155,                   /* $@52  */
  YYSYMBOL_156_53 = 156,                   /* $@53  */
  YYSYMBOL_do_clause = 157,                /* do_clause  */
  YYSYMBOL_158_54 = 158,                   /* $@54  */
  YYSYMBOL_159_55 = 159,                   /* $@55  */
  YYSYMBOL_160_56 = 160,                   /* $@56  */
  YYSYMBOL_161_57 = 161,                   /* $@57  */
  YYSYMBOL_case_clause = 162,              /* case_clause  */
  YYSYMBOL_163_58 = 163,                   /* $@58  */
  YYSYMBOL_default_case = 164,             /* default_case  */
  YYSYMBOL_165_59 = 165,                   /* $@59  */
  YYSYMBOL_case_body = 166,                /* case_body  */
  YYSYMBOL_switch_clause_intro = 167,      /* switch_clause_intro  */
  YYSYMBOL_168_60 = 168,                   /* $@60  */
  YYSYMBOL_169_61 = 169,                   /* $@61  */
  YYSYMBOL_170_62 = 170,                   /* $@62  */
  YYSYMBOL_switch_clause = 171,            /* switch_clause  */
  YYSYMBOL_172_63 = 172,                   /* $@63  */
  YYSYMBOL_type_cast = 173,                /* type_cast  */
  YYSYMBOL_174_64 = 174,                   /* $@64  */
  YYSYMBOL_assignment_target = 175,        /* assignment_target  */
  YYSYMBOL_assignment = 176,               /* assignment  */
  YYSYMBOL_177_65 = 177                    /* $@65  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   340

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  122
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  313

#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    42,     2,     2,
      48,    49,    40,    38,    46,    39,    45,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    50,
       2,    53,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,    44,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    39,    39,    43,    44,    48,    49,    56,    57,    61,
      62,    63,    64,    65,    66,    70,    71,    75,    76,    80,
      81,    81,    81,    81,    85,    86,    93,    93,   100,   101,
     102,   103,   107,   108,   112,   112,   112,   112,   112,   119,
     119,   119,   123,   124,   125,   125,   126,   130,   134,   135,
     135,   142,   142,   146,   147,   151,   152,   156,   156,   156,
     156,   156,   156,   156,   156,   160,   161,   162,   163,   164,
     165,   166,   167,   171,   172,   176,   176,   176,   177,   181,
     181,   181,   181,   181,   185,   185,   192,   192,   192,   193,
     193,   193,   197,   198,   201,   202,   202,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   234,   235,   239,   240,   241,
     245,   245,   245,   245,   245,   245,   246,   246,   253,   254,
     259,   260,   264,   265,   269,   270,   274,   275,   275,   275,
     282,   283,   284,   288,   288,   288,   289,   289,   294,   294,
     298,   299,   303,   303,   303,   310,   310,   310,   311,   311,
     315,   316,   317,   321,   321,   321,   328,   328,   328,   332,
     332,   332,   332,   332,   339,   339,   343,   343,   347,   348,
     352,   352,   352,   352,   356,   357,   357,   364,   364,   368,
     369,   370,   371,   372,   376,   376
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NOTHING", "IMPORT",
  "CLASS", "METHOD", "CREATE", "DESTROY", "DICT", "LIST", "BOOL", "TRUE",
  "FALSE", "STRING", "NUM", "FOR", "IF", "ELSE", "WHILE", "DO", "SWITCH",
  "CASE", "BREAK", "CONTINUE", "DEFAULT", "SYMBOL", "NUMBER", "QSTRG",
  "AND", "OR", "NOT", "EQU", "NEQU", "LTEQU", "GTEQU", "LESS", "MORE",
  "'+'", "'-'", "'*'", "'/'", "'%'", "NEG", "'~'", "'.'", "','", "':'",
  "'('", "')'", "';'", "'{'", "'}'", "'='", "'['", "']'", "$accept",
  "module", "module_item", "module_list", "complex_name", "intrinsic_type",
  "formatted_string_param", "formatted_string_param_list",
  "formatted_string", "$@1", "$@2", "$@3", "bool_value",
  "import_definition", "$@4", "class_body_item", "class_body",
  "class_definition", "$@5", "$@6", "$@7", "$@8", "class_data_definition",
  "$@9", "$@10", "function_data_definition_target", "$@11",
  "function_data_definition_symbol", "function_data_definition", "$@12",
  "method_def_param", "$@13", "method_def_param_list", "method_param_def",
  "method_definition", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19",
  "$@20", "method_body_element", "method_body_element_list", "method_body",
  "$@21", "$@22", "constructor_definition", "$@23", "$@24", "$@25", "$@26",
  "destructor_definition", "$@27", "subscript_item", "$@28", "$@29",
  "$@30", "$@31", "subscript_list", "expression_name", "$@32",
  "expression", "function_call_parameter", "function_call_parameter_list",
  "function_call", "$@33", "$@34", "$@35", "$@36", "$@37", "$@38",
  "branch_expression", "jump_clause", "loop_body_element",
  "loop_body_element_list", "loop_body", "$@39", "$@40",
  "for_initialize_assign", "for_initialize", "$@41", "$@42", "$@43",
  "for_test_expression", "$@44", "for_arith_expression", "for_clause",
  "$@45", "$@46", "else_clause", "$@47", "$@48", "$@49", "else_body",
  "if_clause", "$@50", "$@51", "while_clause", "$@52", "$@53", "do_clause",
  "$@54", "$@55", "$@56", "$@57", "case_clause", "$@58", "default_case",
  "$@59", "case_body", "switch_clause_intro", "$@60", "$@61", "$@62",
  "switch_clause", "$@63", "type_cast", "$@64", "assignment_target",
  "assignment", "$@65", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    43,    45,
      42,    47,    37,   293,   126,    46,    44,    58,    40,    41,
      59,   123,   125,    61,    91,    93
};
#endif

#define YYPACT_NINF (-120)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-195)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,     0,  -120,    81,  -120,  -120,  -120,  -120,  -120,     8,
    -120,  -120,     5,  -120,  -120,    15,    16,    28,  -120,   226,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,    37,
    -120,  -120,   226,  -120,  -120,  -120,  -120,    64,    47,    53,
      79,    86,  -120,    65,  -120,  -120,    71,  -120,  -120,  -120,
    -120,    73,   187,  -120,   253,    78,  -120,  -120,  -120,    85,
    -120,   106,    89,   101,   104,  -120,   105,    35,   129,  -120,
    -120,   253,  -120,  -120,  -120,  -120,  -120,    -5,  -120,   109,
    -120,   187,   130,   187,   113,    37,  -120,  -120,  -120,   114,
    -120,   116,   124,  -120,     6,  -120,   117,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,   132,   187,    -3,    -3,   128,
    -120,   161,  -120,    88,  -120,  -120,  -120,   114,   131,   118,
      53,  -120,   -26,  -120,   161,  -120,  -120,  -120,  -120,   161,
     161,   161,     4,  -120,  -120,   248,  -120,  -120,  -120,   234,
     172,   248,   -10,  -120,   159,     3,  -120,  -120,  -120,   248,
     161,  -120,   115,  -120,  -120,   146,  -120,   181,   248,   161,
     158,  -120,  -120,   189,   156,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   162,   165,
     166,   167,  -120,  -120,  -120,   234,   164,   190,  -120,   248,
    -120,   169,   199,   200,   248,  -120,  -120,   206,   248,  -120,
    -120,  -120,   209,    39,   248,  -120,  -120,  -120,  -120,   237,
    -120,   156,   259,   259,   268,   268,    69,    69,    69,    69,
     163,   163,  -120,  -120,  -120,    -7,   114,  -120,  -120,  -120,
     214,  -120,   220,   -10,   227,   263,  -120,  -120,   161,   187,
     222,  -120,   264,   161,   284,  -120,   266,  -120,  -120,   297,
    -120,  -120,    -3,  -120,  -120,   269,  -120,   248,  -120,   145,
     114,   248,  -120,  -120,    53,  -120,  -120,   294,  -120,   147,
     270,  -120,  -120,   248,   271,  -120,   265,   267,   161,  -120,
     274,   291,  -120,   294,   -10,  -120,  -120,   278,   248,  -120,
    -120,  -120,  -120,   248,   275,  -120,  -120,   169,   147,   277,
      53,   279,  -120,   114,   280,  -120,  -120,  -120,    53,  -120,
     281,  -120,  -120
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    34,     0,     5,     2,     3,     4,    26,     0,
       1,     6,     0,    35,    27,     0,     0,     0,    36,     0,
      57,    79,    84,     9,    10,    11,    12,    13,     7,    14,
      39,    32,    37,    28,    29,    30,    31,     0,     0,     0,
       0,     0,    33,     0,    58,    80,    75,    85,     8,    40,
      38,     0,    56,    78,     0,     0,    59,    51,    53,    55,
      81,     0,     0,     0,     0,   169,     0,    14,     0,    65,
      73,    76,    66,    67,    68,    69,    70,     0,    71,     0,
      41,    56,     0,     0,     0,   126,   152,   163,   166,     0,
     180,     0,     0,    47,     0,    74,     0,   176,   184,   185,
      72,    60,    52,    54,    82,     0,     0,     0,     0,   137,
     170,     0,   121,     0,    48,    49,    77,     0,     0,     0,
       0,   127,    14,   143,     0,   146,    24,    25,    97,     0,
       0,     0,    94,   129,    98,   128,   164,   167,   136,     0,
       0,   181,   117,   192,    19,    94,   187,   190,   193,   189,
       0,   195,     0,   177,   186,     0,    83,     0,   148,     0,
       0,   113,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,   138,     0,     0,   115,   116,
     118,   122,     0,     0,   191,    42,    46,     0,    43,    44,
      61,   144,     0,    94,   150,   153,   151,   147,   114,    86,
      92,    96,   104,   105,   108,   109,   110,   111,   106,   107,
      99,   100,   102,   101,   103,     0,     0,   131,   130,   135,
       0,   171,     0,     0,     0,     0,   188,    50,     0,    56,
       0,   149,     0,     0,     0,    93,   158,   162,   160,   165,
     168,   139,     0,   182,   119,     0,    21,    45,    62,     0,
       0,    87,    90,   155,     0,   161,   172,     0,   123,     0,
       0,   140,   142,   141,     0,   154,     0,     0,     0,   159,
       0,     0,   178,   183,   117,    15,    17,    22,    16,    63,
     145,    88,    91,   156,     0,   174,   179,   124,     0,     0,
       0,     0,   173,     0,     0,    18,    23,    64,     0,   175,
       0,   157,   125
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,   324,  -120,   -19,   -17,    32,  -120,  -106,  -120,
    -120,  -120,  -108,  -120,  -120,   300,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
     250,  -120,  -120,   -78,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,   -32,  -120,  -119,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,   123,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,   -99,   102,    52,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -102,  -120,   152,  -120,  -113,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
      90,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,    55,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,   188,  -120,  -120,
     -98,  -120
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,   132,    57,   286,   287,   188,   192,
     269,   299,   133,     6,    12,    31,    32,     7,     9,    15,
      19,    43,    33,    41,    55,   197,   238,    94,    69,   152,
      58,    82,    59,    60,    34,    37,    51,    81,   119,   239,
     270,   300,   182,    71,    47,    54,    96,    35,    38,    52,
      84,   120,    36,    39,   210,   243,   276,   244,   277,   211,
     134,   164,   135,   190,   191,    72,    91,   142,   234,   284,
     304,   105,   136,   183,   184,   185,   110,   139,   230,   274,
     124,   157,   240,   160,   159,   202,   205,    73,   106,   242,
     248,   278,   301,   264,   249,    74,   107,   178,    75,   108,
     179,    76,    89,   140,   252,   280,   282,   303,    99,   117,
     283,    77,   111,   187,   267,    78,   118,   150,   193,   151,
      79,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   156,    30,   101,   153,   148,   137,   147,   125,   126,
     127,   246,   141,    29,   149,    30,    28,   128,   144,    40,
      97,   129,    70,    28,   128,   158,     8,  -194,   129,   130,
     161,   162,   163,    29,    13,    67,   130,    68,   131,    95,
       1,     2,    85,   189,    46,   131,   196,    98,    40,    40,
     -14,   194,    67,   198,    68,    14,   114,   -95,   -95,   115,
     204,   206,    29,    16,    29,    17,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,    18,
      40,    10,    40,  -120,    40,     1,     2,   122,  -194,   123,
      44,   143,  -194,   -95,   145,    45,   146,    23,    24,    25,
     126,   127,    26,    27,    46,    48,   247,   173,   174,   175,
     176,   177,    49,   250,    28,   128,   144,    50,   195,   129,
      67,    56,    68,    53,    23,    24,    25,   130,    80,    26,
      27,    83,    28,   145,   189,   146,   131,    86,   262,   257,
     203,    28,   128,   144,   261,   279,   129,   275,   271,    87,
     266,   272,    88,    90,   130,    93,   102,   126,   127,   100,
     273,   258,   104,   131,   112,   109,    67,   155,    68,   116,
     288,    28,   128,    28,   128,   285,   129,   113,   129,   293,
     138,   307,   121,   154,   130,   189,   130,    28,   128,   311,
     309,   186,   129,   131,   200,   131,    23,    24,    25,   288,
     130,    26,    27,   175,   176,   177,   -20,   201,   207,   131,
     209,   225,   231,    28,   226,   233,   227,   228,   165,   166,
      29,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,    20,    21,    22,    23,    24,    25,   208,   232,
      26,    27,    61,    23,    24,    25,   235,   236,    26,    27,
      62,    63,    28,    64,    65,    66,   237,   180,   181,   241,
      28,    61,    23,    24,    25,   -89,   251,    26,    27,    62,
      63,   253,    64,    65,    66,   259,   255,   165,   166,    28,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   256,   144,   260,   263,   246,   281,   268,   295,   289,
     291,   290,   292,   294,   298,   302,   306,    11,   308,   310,
     305,   312,    42,   103,   245,   254,   297,   229,   296,   265,
     199
};

static const yytype_int16 yycheck[] =
{
      19,   120,    19,    81,   117,   113,   108,   113,   106,    12,
      13,    18,   111,    32,   113,    32,    26,    27,    28,    45,
      25,    31,    54,    26,    27,   124,    26,    53,    31,    39,
     129,   130,   131,    52,    26,    54,    39,    54,    48,    71,
       4,     5,    61,   142,    51,    48,   152,    52,    45,    45,
      47,   150,    71,   152,    71,    50,    50,    54,    54,    53,
     159,   159,    81,    48,    83,    49,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,    51,
      45,     0,    45,    48,    45,     4,     5,   106,    53,   106,
      26,     3,    53,    54,   113,    48,   113,     9,    10,    11,
      12,    13,    14,    15,    51,    26,   225,    38,    39,    40,
      41,    42,    26,   226,    26,    27,    28,    52,     3,    31,
     139,    48,   139,    52,     9,    10,    11,    39,    50,    14,
      15,    46,    26,   152,   233,   152,    48,    48,   244,   238,
     159,    26,    27,    28,   243,   264,    31,   260,     3,    48,
     252,   259,    48,    48,    39,    26,    26,    12,    13,    50,
     259,   239,    49,    48,    48,    51,   185,    49,   185,    52,
     269,    26,    27,    26,    27,    28,    31,    53,    31,   278,
      52,   300,    50,    52,    39,   284,    39,    26,    27,   308,
     303,    19,    31,    48,    48,    48,     9,    10,    11,   298,
      39,    14,    15,    40,    41,    42,    47,    26,    50,    48,
      54,    49,    48,    26,    49,    46,    50,    50,    29,    30,
     239,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,     6,     7,     8,     9,    10,    11,    49,    49,
      14,    15,     8,     9,    10,    11,    47,    47,    14,    15,
      16,    17,    26,    19,    20,    21,    50,    23,    24,    50,
      26,     8,     9,    10,    11,    28,    52,    14,    15,    16,
      17,    51,    19,    20,    21,    53,    49,    29,    30,    26,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    48,    28,    49,    48,    18,    22,    48,    27,    49,
      55,    50,    55,    49,    46,    50,    49,     3,    49,    49,
     298,    50,    32,    83,   211,   233,   284,   185,   283,   249,
     152
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    57,    58,    59,    69,    73,    26,    74,
       0,    58,    70,    26,    50,    75,    48,    49,    51,    76,
       6,     7,     8,     9,    10,    11,    14,    15,    26,    60,
      61,    71,    72,    78,    90,   103,   108,    91,   104,   109,
      45,    79,    71,    77,    26,    48,    51,   100,    26,    26,
      52,    92,   105,    52,   101,    80,    48,    61,    86,    88,
      89,     8,    16,    17,    19,    20,    21,    60,    61,    84,
      98,    99,   121,   143,   151,   154,   157,   167,   171,   176,
      50,    93,    87,    46,   106,    60,    48,    48,    48,   158,
      48,   122,   177,    26,    83,    98,   102,    25,    52,   164,
      50,    89,    26,    86,    49,   127,   144,   152,   155,    51,
     132,   168,    48,    53,    50,    53,    52,   165,   172,    94,
     107,    50,    60,    61,   136,   176,    12,    13,    27,    31,
      39,    48,    60,    68,   116,   118,   128,   128,    52,   133,
     159,   118,   123,     3,    28,    60,    61,    64,    68,   118,
     173,   175,    85,   132,    52,    49,   100,   137,   118,   140,
     139,   118,   118,   118,   117,    29,    30,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,   153,   156,
      23,    24,    98,   129,   130,   131,    19,   169,    64,   118,
     119,   120,    65,   174,   118,     3,    64,    81,   118,   173,
      48,    26,   141,    60,   118,   142,   176,    50,    49,    54,
     110,   115,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,    49,    49,    50,    50,   130,
     134,    48,    49,    46,   124,    47,    47,    50,    82,    95,
     138,    50,   145,   111,   113,   110,    18,   100,   146,   150,
     132,    52,   160,    51,   119,    49,    48,   118,    89,    53,
      49,   118,    64,    48,   149,   146,   128,   170,    48,    66,
      96,     3,    68,   118,   135,   132,   112,   114,   147,   100,
     161,    22,   162,   166,   125,    28,    62,    63,   118,    49,
      50,    55,    55,   118,    49,    27,   162,   120,    46,    67,
      97,   148,    50,   163,   126,    62,    49,   100,    49,   132,
      49,   100,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    61,    62,    62,    63,    63,    64,
      65,    66,    67,    64,    68,    68,    70,    69,    71,    71,
      71,    71,    72,    72,    74,    75,    76,    77,    73,    79,
      80,    78,    81,    81,    82,    81,    81,    83,    84,    85,
      84,    87,    86,    88,    88,    89,    89,    91,    92,    93,
      94,    95,    96,    97,    90,    98,    98,    98,    98,    98,
      98,    98,    98,    99,    99,   101,   102,   100,   100,   104,
     105,   106,   107,   103,   109,   108,   111,   112,   110,   113,
     114,   110,   115,   115,   116,   117,   116,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   119,   119,   120,   120,   120,
     122,   123,   124,   125,   126,   121,   127,   121,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   133,   134,   132,
     135,   135,   135,   137,   138,   136,   139,   136,   141,   140,
     142,   142,   144,   145,   143,   147,   148,   146,   149,   146,
     150,   150,   150,   152,   153,   151,   155,   156,   154,   158,
     159,   160,   161,   157,   163,   162,   165,   164,   166,   166,
     168,   169,   170,   167,   171,   172,   171,   174,   173,   175,
     175,   175,   175,   175,   177,   176
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     0,     0,     8,     1,     1,     0,     4,     1,     1,
       1,     1,     1,     2,     0,     0,     0,     0,    11,     0,
       0,     5,     1,     1,     0,     3,     1,     1,     3,     0,
       6,     0,     3,     1,     3,     1,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     0,     0,     5,     2,     0,
       0,     0,     0,     9,     0,     3,     0,     0,     5,     0,
       0,     5,     1,     2,     1,     0,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     1,     1,     0,     1,     3,
       0,     0,     0,     0,     0,    13,     0,     4,     1,     1,
       2,     2,     1,     1,     1,     2,     2,     0,     0,     5,
       1,     1,     1,     0,     0,     7,     0,     3,     0,     3,
       1,     1,     0,     0,     9,     0,     0,     7,     0,     3,
       1,     2,     1,     0,     0,     7,     0,     0,     7,     0,
       0,     0,     0,    11,     0,     4,     0,     3,     1,     2,
       0,     0,     0,     9,     2,     0,     4,     0,     3,     1,
       1,     2,     1,     1,     0,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 39 "parser.y"
                  {}
#line 1979 "parser.c"
    break;

  case 3:
#line 43 "parser.y"
                        {}
#line 1985 "parser.c"
    break;

  case 4:
#line 44 "parser.y"
                       {}
#line 1991 "parser.c"
    break;

  case 5:
#line 48 "parser.y"
                  {}
#line 1997 "parser.c"
    break;

  case 6:
#line 49 "parser.y"
                         {}
#line 2003 "parser.c"
    break;

  case 7:
#line 56 "parser.y"
             {}
#line 2009 "parser.c"
    break;

  case 8:
#line 57 "parser.y"
                              {}
#line 2015 "parser.c"
    break;

  case 9:
#line 61 "parser.y"
           {}
#line 2021 "parser.c"
    break;

  case 10:
#line 62 "parser.y"
           {}
#line 2027 "parser.c"
    break;

  case 11:
#line 63 "parser.y"
           {}
#line 2033 "parser.c"
    break;

  case 12:
#line 64 "parser.y"
             {}
#line 2039 "parser.c"
    break;

  case 13:
#line 65 "parser.y"
          {}
#line 2045 "parser.c"
    break;

  case 14:
#line 66 "parser.y"
                   {}
#line 2051 "parser.c"
    break;

  case 15:
#line 70 "parser.y"
            {}
#line 2057 "parser.c"
    break;

  case 16:
#line 71 "parser.y"
                 {}
#line 2063 "parser.c"
    break;

  case 17:
#line 75 "parser.y"
                             {}
#line 2069 "parser.c"
    break;

  case 18:
#line 76 "parser.y"
                                                             {}
#line 2075 "parser.c"
    break;

  case 19:
#line 80 "parser.y"
            {}
#line 2081 "parser.c"
    break;

  case 20:
#line 81 "parser.y"
            {}
#line 2087 "parser.c"
    break;

  case 21:
#line 81 "parser.y"
                       {}
#line 2093 "parser.c"
    break;

  case 22:
#line 81 "parser.y"
                                                      {}
#line 2099 "parser.c"
    break;

  case 24:
#line 85 "parser.y"
           {}
#line 2105 "parser.c"
    break;

  case 25:
#line 86 "parser.y"
            {}
#line 2111 "parser.c"
    break;

  case 26:
#line 93 "parser.y"
                    {}
#line 2117 "parser.c"
    break;

  case 27:
#line 93 "parser.y"
                           {}
#line 2123 "parser.c"
    break;

  case 28:
#line 100 "parser.y"
                            {}
#line 2129 "parser.c"
    break;

  case 29:
#line 101 "parser.y"
                        {}
#line 2135 "parser.c"
    break;

  case 30:
#line 102 "parser.y"
                             {}
#line 2141 "parser.c"
    break;

  case 31:
#line 103 "parser.y"
                            {}
#line 2147 "parser.c"
    break;

  case 32:
#line 107 "parser.y"
                      {}
#line 2153 "parser.c"
    break;

  case 33:
#line 108 "parser.y"
                                 {}
#line 2159 "parser.c"
    break;

  case 34:
#line 112 "parser.y"
            {}
#line 2165 "parser.c"
    break;

  case 35:
#line 112 "parser.y"
                      {}
#line 2171 "parser.c"
    break;

  case 36:
#line 112 "parser.y"
                                     {}
#line 2177 "parser.c"
    break;

  case 37:
#line 112 "parser.y"
                                                   {}
#line 2183 "parser.c"
    break;

  case 39:
#line 119 "parser.y"
                     {}
#line 2189 "parser.c"
    break;

  case 40:
#line 119 "parser.y"
                               {}
#line 2195 "parser.c"
    break;

  case 41:
#line 119 "parser.y"
                                      {}
#line 2201 "parser.c"
    break;

  case 42:
#line 123 "parser.y"
              {}
#line 2207 "parser.c"
    break;

  case 43:
#line 124 "parser.y"
                 {}
#line 2213 "parser.c"
    break;

  case 44:
#line 125 "parser.y"
                {}
#line 2219 "parser.c"
    break;

  case 45:
#line 125 "parser.y"
                              {}
#line 2225 "parser.c"
    break;

  case 46:
#line 126 "parser.y"
                       {}
#line 2231 "parser.c"
    break;

  case 47:
#line 130 "parser.y"
             {}
#line 2237 "parser.c"
    break;

  case 48:
#line 134 "parser.y"
                                                         {}
#line 2243 "parser.c"
    break;

  case 49:
#line 135 "parser.y"
                                                         {}
#line 2249 "parser.c"
    break;

  case 50:
#line 135 "parser.y"
                                                                                                {}
#line 2255 "parser.c"
    break;

  case 51:
#line 142 "parser.y"
                     {}
#line 2261 "parser.c"
    break;

  case 52:
#line 142 "parser.y"
                               {}
#line 2267 "parser.c"
    break;

  case 53:
#line 146 "parser.y"
                       {}
#line 2273 "parser.c"
    break;

  case 54:
#line 147 "parser.y"
                                                 {}
#line 2279 "parser.c"
    break;

  case 55:
#line 151 "parser.y"
                             {}
#line 2285 "parser.c"
    break;

  case 56:
#line 152 "parser.y"
                   {}
#line 2291 "parser.c"
    break;

  case 57:
#line 156 "parser.y"
             {}
#line 2297 "parser.c"
    break;

  case 58:
#line 156 "parser.y"
                       {}
#line 2303 "parser.c"
    break;

  case 59:
#line 156 "parser.y"
                              {}
#line 2309 "parser.c"
    break;

  case 60:
#line 156 "parser.y"
                                                  {}
#line 2315 "parser.c"
    break;

  case 61:
#line 156 "parser.y"
                                                             {}
#line 2321 "parser.c"
    break;

  case 62:
#line 156 "parser.y"
                                                                                 {}
#line 2327 "parser.c"
    break;

  case 63:
#line 156 "parser.y"
                                                                                        {}
#line 2333 "parser.c"
    break;

  case 64:
#line 156 "parser.y"
                                                                                                       {}
#line 2339 "parser.c"
    break;

  case 65:
#line 160 "parser.y"
                               {}
#line 2345 "parser.c"
    break;

  case 66:
#line 161 "parser.y"
                    {}
#line 2351 "parser.c"
    break;

  case 67:
#line 162 "parser.y"
                 {}
#line 2357 "parser.c"
    break;

  case 68:
#line 163 "parser.y"
                {}
#line 2363 "parser.c"
    break;

  case 69:
#line 164 "parser.y"
                   {}
#line 2369 "parser.c"
    break;

  case 70:
#line 165 "parser.y"
                {}
#line 2375 "parser.c"
    break;

  case 71:
#line 166 "parser.y"
                    {}
#line 2381 "parser.c"
    break;

  case 72:
#line 167 "parser.y"
                     {}
#line 2387 "parser.c"
    break;

  case 73:
#line 171 "parser.y"
                          {}
#line 2393 "parser.c"
    break;

  case 74:
#line 172 "parser.y"
                                                   {}
#line 2399 "parser.c"
    break;

  case 75:
#line 176 "parser.y"
          {}
#line 2405 "parser.c"
    break;

  case 76:
#line 176 "parser.y"
                                      {}
#line 2411 "parser.c"
    break;

  case 77:
#line 176 "parser.y"
                                             {}
#line 2417 "parser.c"
    break;

  case 78:
#line 177 "parser.y"
              {}
#line 2423 "parser.c"
    break;

  case 79:
#line 181 "parser.y"
             {}
#line 2429 "parser.c"
    break;

  case 80:
#line 181 "parser.y"
                    {}
#line 2435 "parser.c"
    break;

  case 81:
#line 181 "parser.y"
                                        {}
#line 2441 "parser.c"
    break;

  case 82:
#line 181 "parser.y"
                                               {}
#line 2447 "parser.c"
    break;

  case 83:
#line 181 "parser.y"
                                                              {}
#line 2453 "parser.c"
    break;

  case 84:
#line 185 "parser.y"
              {}
#line 2459 "parser.c"
    break;

  case 85:
#line 185 "parser.y"
                             {}
#line 2465 "parser.c"
    break;

  case 86:
#line 192 "parser.y"
          {}
#line 2471 "parser.c"
    break;

  case 87:
#line 192 "parser.y"
                        {}
#line 2477 "parser.c"
    break;

  case 89:
#line 193 "parser.y"
          {}
#line 2483 "parser.c"
    break;

  case 90:
#line 193 "parser.y"
                              {}
#line 2489 "parser.c"
    break;

  case 92:
#line 197 "parser.y"
                     {}
#line 2495 "parser.c"
    break;

  case 93:
#line 198 "parser.y"
                                    {}
#line 2501 "parser.c"
    break;

  case 94:
#line 201 "parser.y"
                   {}
#line 2507 "parser.c"
    break;

  case 95:
#line 202 "parser.y"
                   {}
#line 2513 "parser.c"
    break;

  case 96:
#line 202 "parser.y"
                                     {}
#line 2519 "parser.c"
    break;

  case 97:
#line 206 "parser.y"
             {}
#line 2525 "parser.c"
    break;

  case 98:
#line 207 "parser.y"
                      {}
#line 2531 "parser.c"
    break;

  case 99:
#line 208 "parser.y"
                                {}
#line 2537 "parser.c"
    break;

  case 100:
#line 209 "parser.y"
                                {}
#line 2543 "parser.c"
    break;

  case 101:
#line 210 "parser.y"
                                {}
#line 2549 "parser.c"
    break;

  case 102:
#line 211 "parser.y"
                                {}
#line 2555 "parser.c"
    break;

  case 103:
#line 212 "parser.y"
                                {}
#line 2561 "parser.c"
    break;

  case 104:
#line 213 "parser.y"
                                {}
#line 2567 "parser.c"
    break;

  case 105:
#line 214 "parser.y"
                               {}
#line 2573 "parser.c"
    break;

  case 106:
#line 215 "parser.y"
                                 {}
#line 2579 "parser.c"
    break;

  case 107:
#line 216 "parser.y"
                                 {}
#line 2585 "parser.c"
    break;

  case 108:
#line 217 "parser.y"
                                {}
#line 2591 "parser.c"
    break;

  case 109:
#line 218 "parser.y"
                                 {}
#line 2597 "parser.c"
    break;

  case 110:
#line 219 "parser.y"
                                  {}
#line 2603 "parser.c"
    break;

  case 111:
#line 220 "parser.y"
                                  {}
#line 2609 "parser.c"
    break;

  case 112:
#line 221 "parser.y"
                               {}
#line 2615 "parser.c"
    break;

  case 113:
#line 222 "parser.y"
                     {}
#line 2621 "parser.c"
    break;

  case 115:
#line 234 "parser.y"
                       {}
#line 2627 "parser.c"
    break;

  case 116:
#line 235 "parser.y"
                 {}
#line 2633 "parser.c"
    break;

  case 118:
#line 240 "parser.y"
                              {}
#line 2639 "parser.c"
    break;

  case 119:
#line 241 "parser.y"
                                                               {}
#line 2645 "parser.c"
    break;

  case 120:
#line 245 "parser.y"
                   {}
#line 2651 "parser.c"
    break;

  case 121:
#line 245 "parser.y"
                          {}
#line 2657 "parser.c"
    break;

  case 122:
#line 245 "parser.y"
                                                          {}
#line 2663 "parser.c"
    break;

  case 123:
#line 245 "parser.y"
                                                                     {}
#line 2669 "parser.c"
    break;

  case 124:
#line 245 "parser.y"
                                                                                                     {}
#line 2675 "parser.c"
    break;

  case 125:
#line 245 "parser.y"
                                                                                                                {}
#line 2681 "parser.c"
    break;

  case 126:
#line 246 "parser.y"
                           {}
#line 2687 "parser.c"
    break;

  case 127:
#line 246 "parser.y"
                                  {}
#line 2693 "parser.c"
    break;

  case 128:
#line 253 "parser.y"
                 {}
#line 2699 "parser.c"
    break;

  case 129:
#line 254 "parser.y"
                 {}
#line 2705 "parser.c"
    break;

  case 130:
#line 259 "parser.y"
                   {}
#line 2711 "parser.c"
    break;

  case 131:
#line 260 "parser.y"
                {}
#line 2717 "parser.c"
    break;

  case 132:
#line 264 "parser.y"
                          {}
#line 2723 "parser.c"
    break;

  case 133:
#line 265 "parser.y"
                  {}
#line 2729 "parser.c"
    break;

  case 134:
#line 269 "parser.y"
                        {}
#line 2735 "parser.c"
    break;

  case 135:
#line 270 "parser.y"
                                               {}
#line 2741 "parser.c"
    break;

  case 136:
#line 274 "parser.y"
              {}
#line 2747 "parser.c"
    break;

  case 137:
#line 275 "parser.y"
          {}
#line 2753 "parser.c"
    break;

  case 138:
#line 275 "parser.y"
                                    {}
#line 2759 "parser.c"
    break;

  case 139:
#line 275 "parser.y"
                                           {}
#line 2765 "parser.c"
    break;

  case 140:
#line 282 "parser.y"
              {}
#line 2771 "parser.c"
    break;

  case 141:
#line 283 "parser.y"
                 {}
#line 2777 "parser.c"
    break;

  case 142:
#line 284 "parser.y"
                 {}
#line 2783 "parser.c"
    break;

  case 143:
#line 288 "parser.y"
                     {}
#line 2789 "parser.c"
    break;

  case 144:
#line 288 "parser.y"
                               {}
#line 2795 "parser.c"
    break;

  case 145:
#line 288 "parser.y"
                                                                {}
#line 2801 "parser.c"
    break;

  case 146:
#line 289 "parser.y"
                 {}
#line 2807 "parser.c"
    break;

  case 147:
#line 289 "parser.y"
                        {}
#line 2813 "parser.c"
    break;

  case 148:
#line 294 "parser.y"
                 {}
#line 2819 "parser.c"
    break;

  case 149:
#line 294 "parser.y"
                        {}
#line 2825 "parser.c"
    break;

  case 150:
#line 298 "parser.y"
                 {}
#line 2831 "parser.c"
    break;

  case 151:
#line 299 "parser.y"
                 {}
#line 2837 "parser.c"
    break;

  case 152:
#line 303 "parser.y"
              {}
#line 2843 "parser.c"
    break;

  case 153:
#line 303 "parser.y"
                                                                          {}
#line 2849 "parser.c"
    break;

  case 154:
#line 303 "parser.y"
                                                                                           {}
#line 2855 "parser.c"
    break;

  case 155:
#line 310 "parser.y"
               {}
#line 2861 "parser.c"
    break;

  case 156:
#line 310 "parser.y"
                             {}
#line 2867 "parser.c"
    break;

  case 157:
#line 310 "parser.y"
                                                {}
#line 2873 "parser.c"
    break;

  case 158:
#line 311 "parser.y"
           {}
#line 2879 "parser.c"
    break;

  case 159:
#line 311 "parser.y"
                          {}
#line 2885 "parser.c"
    break;

  case 160:
#line 315 "parser.y"
                  {}
#line 2891 "parser.c"
    break;

  case 161:
#line 316 "parser.y"
                            {}
#line 2897 "parser.c"
    break;

  case 162:
#line 317 "parser.y"
                  {}
#line 2903 "parser.c"
    break;

  case 163:
#line 321 "parser.y"
             {}
#line 2909 "parser.c"
    break;

  case 164:
#line 321 "parser.y"
                                  {}
#line 2915 "parser.c"
    break;

  case 165:
#line 321 "parser.y"
                                                   {}
#line 2921 "parser.c"
    break;

  case 166:
#line 328 "parser.y"
                {}
#line 2927 "parser.c"
    break;

  case 167:
#line 328 "parser.y"
                                     {}
#line 2933 "parser.c"
    break;

  case 168:
#line 328 "parser.y"
                                                      {}
#line 2939 "parser.c"
    break;

  case 169:
#line 332 "parser.y"
         {}
#line 2945 "parser.c"
    break;

  case 170:
#line 332 "parser.y"
                      {}
#line 2951 "parser.c"
    break;

  case 171:
#line 332 "parser.y"
                                   {}
#line 2957 "parser.c"
    break;

  case 172:
#line 332 "parser.y"
                                                        {}
#line 2963 "parser.c"
    break;

  case 173:
#line 332 "parser.y"
                                                                   {}
#line 2969 "parser.c"
    break;

  case 174:
#line 339 "parser.y"
                  {}
#line 2975 "parser.c"
    break;

  case 175:
#line 339 "parser.y"
                               {}
#line 2981 "parser.c"
    break;

  case 176:
#line 343 "parser.y"
              {}
#line 2987 "parser.c"
    break;

  case 177:
#line 343 "parser.y"
                           {}
#line 2993 "parser.c"
    break;

  case 178:
#line 347 "parser.y"
                  {}
#line 2999 "parser.c"
    break;

  case 179:
#line 348 "parser.y"
                            {}
#line 3005 "parser.c"
    break;

  case 180:
#line 352 "parser.y"
                 {}
#line 3011 "parser.c"
    break;

  case 181:
#line 352 "parser.y"
                               {}
#line 3017 "parser.c"
    break;

  case 182:
#line 352 "parser.y"
                                          {}
#line 3023 "parser.c"
    break;

  case 183:
#line 352 "parser.y"
                                                       {}
#line 3029 "parser.c"
    break;

  case 184:
#line 356 "parser.y"
                              {}
#line 3035 "parser.c"
    break;

  case 185:
#line 357 "parser.y"
                                       {}
#line 3041 "parser.c"
    break;

  case 186:
#line 357 "parser.y"
                                              {}
#line 3047 "parser.c"
    break;

  case 187:
#line 364 "parser.y"
                     {}
#line 3053 "parser.c"
    break;

  case 188:
#line 364 "parser.y"
                            {}
#line 3059 "parser.c"
    break;

  case 189:
#line 368 "parser.y"
                 {}
#line 3065 "parser.c"
    break;

  case 190:
#line 369 "parser.y"
                       {}
#line 3071 "parser.c"
    break;

  case 191:
#line 370 "parser.y"
                           {}
#line 3077 "parser.c"
    break;

  case 192:
#line 371 "parser.y"
              {}
#line 3083 "parser.c"
    break;

  case 193:
#line 372 "parser.y"
                 {}
#line 3089 "parser.c"
    break;

  case 194:
#line 376 "parser.y"
                   {}
#line 3095 "parser.c"
    break;

  case 195:
#line 376 "parser.y"
                                            {}
#line 3101 "parser.c"
    break;


#line 3105 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  // Pop stack until we find a state that shifts the error token.
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 379 "parser.y"


#include <stdio.h>

extern char yytext[];

void yyerror(const char* s)
{
	fflush(stdout);
	fprintf(stdout, "\n%s: line %d: at %d: %s\n\n", get_file_name(), get_line_number(), get_col_number(), s);
    inc_error_count();
}
