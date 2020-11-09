
#include "common.h"
#include <math.h>

/**
 * @brief This function validates that the left and the right factors are
 * compatible. Return the likely result of the operation. Return 0 if there
 * is an error.
 */
int _arith_lr(_expr_element* left, _expr_element* right) {

    int retv = 0; // pessimestic

    switch(left->type) {
        case EXP_INT:
            switch(right->type) {
                case EXP_INT:
                    retv = EXP_INT;
                    break;

                case EXP_STRING:
                    syntax("arithmetic operation on a integer and a string is invalid. (use a cast)");
                    break;

                case EXP_FLOAT:
                    warning("integer on the left is promoted to a float");
                    left->fpnum = (double)left->intnum;
                    retv = EXP_FLOAT;
                    break;

                case EXP_BOOL:
                    syntax("arithmetic operation on string and bool is invalid. (use a cast)");
                    break;
            }
            break;

        case EXP_FLOAT:
            switch(right->type) {
                case EXP_INT:
                    warning("integer value on the right is promoted to float");
                    right->fpnum = (double)right->intnum;
                    break;

                case EXP_FLOAT:
                    retv = EXP_FLOAT;
                    break;

                case EXP_STRING:
                    syntax("arithmetic operation on a number and a string is invalid. (use a cast)");
                    break;

                case EXP_BOOL:
                    syntax("arithmetic operation on number and bool is invalid. (use a cast)");
                    break;
            }
            break;
        case EXP_STRING:
            switch(right->type) {
                case EXP_INT:
                    syntax("arithmetic operation on a number and a string is invalid. (use a cast)");
                    break;

                case EXP_STRING:
                    retv = EXP_STRING;
                    break;

                case EXP_FLOAT:
                    syntax("arithmetic operation on a number and a string is invalid. (use a cast)");
                    break;

                case EXP_BOOL:
                    syntax("arithmetic operation on string and bool is invalid. (use a cast)");
                    break;
            }
            break;
        case EXP_BOOL:
            switch(right->type) {
                case EXP_INT:
                    warning("integer on the right is truncated to boolean");
                    break;

                case EXP_BOOL:
                    retv = EXP_BOOL;
                    break;

                case EXP_STRING:
                    syntax("arithmetic operation on string and bool is invalid. (use a cast)");
                    break;

                case EXP_FLOAT:
                    syntax("arithmetic operation on float and bool is invalid. (use a cast)");
                    break;
            }
            break;
    }
    return retv;
}

/**
 * @brief This function validates an arithmetic operation.
 *
 * TODO: add logic to see if the result is a valid type
 */
int _arithmetic(int op) {

    _MARK(5);
    _expr_element left;
    _expr_element right;
    _expr_element result;
    int apparent_type;  // number, bool, or string
    int retv = 0;

    if(!_expr_pop(&right))
        fatal_error("expression stack underflow on right operand (parser error)");
    if(!_expr_pop(&left))
        fatal_error("expression stack underflow on left operand (parser error)");

    if(0 == (apparent_type = _arith_lr(&left, &right))) {
        _DEBUG(5, "expr_error: %s -> %s = %s",
               EXPR_TYPE_TO_STR(left.type),
               EXPR_TYPE_TO_STR(right.type),
               EXPR_TYPE_TO_STR(apparent_type));
        return EXP_ERROR;
    }


    memset(&result, 0, sizeof(_expr_element));
    result.type = EXP_FLOAT;

    switch(op) {
        case EXP_ADD_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.intnum = left.intnum + right.intnum;
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.fpnum = left.fpnum + right.fpnum;
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    result.type = EXP_STRING;
                    result.str = alloc_cat(left.str, right.str);
                    _expr_push(&result);
                    FREE(right.str);
                    FREE(left.str);
                    break;

                case EXP_BOOL:
                    syntax("addition on a boolean value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                default:
                    fatal_error("invalid value type in expression (parser error)");
                    break;
            }
            break;

        case EXP_SUB_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.intnum = left.intnum - right.intnum;
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.fpnum = left.fpnum - right.fpnum;
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("subtraction on a string value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                case EXP_BOOL:
                    syntax("subtraction on a boolean value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                default:
                    fatal_error("invalid value type in expression (parser error)");
                    break;
            }
            break;

        case EXP_MUL_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.intnum = left.intnum * right.intnum;
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.fpnum = left.fpnum * right.fpnum;
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("multiplication on a string value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                case EXP_BOOL:
                    syntax("multiplication on a boolean value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                default:
                    fatal_error("invalid value type in expression (parser error)");
                    break;
            }
            break;

        case EXP_DIV_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    if(right.intnum == 0) {
                        syntax("right side of division cannot be zero.");
                        fatal_error("divide by zero error");
                    }
                    result.intnum = left.intnum / right.intnum;
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    if(right.fpnum == 0.0) {
                        syntax("right side of division cannot be zero.");
                        fatal_error("divide by zero error");
                    }
                    result.fpnum = left.fpnum / right.fpnum;
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("division on a string value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                case EXP_BOOL:
                    syntax("division on a boolean value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                default:
                    fatal_error("invalid value type in expression (parser error)");
                    break;
            }

            break;

        case EXP_MOD_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    if(right.intnum == 0) {
                        syntax("right side of modulo cannot be zero.");
                        fatal_error("divide by zero error");
                    }
                    result.intnum = left.intnum % right.intnum;
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    if(right.fpnum == 0.0) {
                        syntax("right side of modulo cannot be zero.");
                        fatal_error("divide by zero error");
                    }
                    result.fpnum = remainder(left.fpnum, right.fpnum);
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("division on a string value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                case EXP_BOOL:
                    syntax("division on a boolean value is invalid");
                    result.type = EXP_ERROR;
                    _expr_push(&result);
                    retv = 1;
                    break;

                default:
                    fatal_error("invalid value type in expression (parser error)");
                    break;
            }
            break;

        default:
            fatal_error("unknown operator in validate aritmetic (parser error)");
    }
    return retv;
}
