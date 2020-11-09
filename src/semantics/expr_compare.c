
#include "common.h"
#include <math.h>

/**
 * @brief This function validates the left and right factors for a magnitude
 * comparison. Returns 1 for valid comparison and 0 for invalid.
 *
 */
int _compare_lr(_expr_element* left, _expr_element* right) {

    int retv = 0; // pessimestic

    switch(left->type) {
        case EXP_INT:
            switch(right->type) {
                case EXP_INT:
                    retv = EXP_INT;
                    break;

                case EXP_FLOAT:
                    warning("float on right is truncated to integer");
                    left->intnum = (long long)left->fpnum;
                    retv = EXP_INT;
                    break;

                case EXP_STRING:
                    syntax("compare a number and a string is invalid. (use a cast)");
                    break;

                case EXP_BOOL:
                    syntax("compare a number and a bool is invalid. (use a cast)");
                    break;
            }
            break;

        case EXP_FLOAT:
            switch(right->type) {
                case EXP_INT:
                    warning("float on left is truncated to an integer");
                    right->intnum = (long long)right->fpnum;
                    retv = EXP_INT;
                    break;

                case EXP_FLOAT:
                    retv = EXP_FLOAT;
                    break;

                case EXP_STRING:
                    syntax("compare a number and a string is invalid. (use a cast)");
                    break;

                case EXP_BOOL:
                    syntax("compare a number and a bool is invalid. (use a cast)");
                    break;
            }
            break;

        case EXP_STRING:
            switch(right->type) {
                case EXP_INT:
                    syntax("compare a integer and a string is invalid. (use a cast)");
                    break;

                case EXP_STRING:
                    retv = EXP_STRING;
                    break;

                case EXP_FLOAT:
                    syntax("compare a float and a string is invalid. (use a cast)");
                    break;

                case EXP_BOOL:
                    syntax("compare a string and a bool is invalid. (use a cast)");
                    break;
            }
            break;

        case EXP_BOOL:
            switch(right->type) {
                case EXP_INT:
                    warning("integer on right truncated to a boolean");
                    right->bool_val = (right->intnum == 0)? 0: 1;
                    retv = EXP_BOOL;
                    break;

                case EXP_BOOL:
                    retv = EXP_BOOL;
                    break;

                case EXP_STRING:
                    syntax("compare a string and bool is invalid. (use a cast)");
                    break;

                case EXP_FLOAT:
                    syntax("compare a float and bool is invalid. (use a cast)");
                    break;
            }
            break;
    }
    return retv;
}

/**
 * @brief This function performs a magnitude compare on two operands. Only operands of
 * the same type can be compared.
 */
int _comparison(int op) {

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

    if(0 == (apparent_type = _compare_lr(&left, &right))) {
        _DEBUG(5, "expr_error: %s -> %s = %s",
               EXPR_TYPE_TO_STR(left.type),
               EXPR_TYPE_TO_STR(right.type),
               EXPR_TYPE_TO_STR(apparent_type));
        _expr_push_error();
        return EXP_ERROR;
    }

    memset(&result, 0, sizeof(_expr_element));
    result.type = EXP_BOOL;

    switch(op) {
        case EXP_EQU_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum == right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum == right.fpnum);
                    _expr_push(&result);
                    warning("comparing two floats for equality is risky");
                    break;

                case EXP_STRING: {
                        int e = strcmp(left.str, right.str);
                        if(e)
                            result.bool_val = 0;
                        else
                            result.bool_val = 1;
                    }
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val == right.bool_val);
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_NEQU_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum != right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum != right.fpnum);
                    _expr_push(&result);
                    warning("comparing two floats for inequality is risky");
                    break;

                case EXP_STRING: {
                        int e = strcmp(left.str, right.str);
                        if(e)
                            result.bool_val = 1;
                        else
                            result.bool_val = 0;
                    }
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val != right.bool_val);
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_LT_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum < right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum < right.fpnum);
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("comparing strings for other then equality does not make sense.");
                    _expr_push_error();
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val < right.bool_val);
                    _expr_push(&result);
                    warning("comparing bools for other than equality may yield unexpected result");
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_GT_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum > right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum > right.fpnum);
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("comparing strings for other then equality does not make sense.");
                    _expr_push_error();
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val > right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_GTE_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum >= right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum >= right.fpnum);
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("comparing strings for other then equality does not make sense.");
                    _expr_push_error();
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val >= right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_LTE_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = (left.intnum <= right.intnum);
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = (left.fpnum <= right.fpnum);
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    syntax("comparing strings for other then equality does not make sense.");
                    _expr_push_error();
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val <= right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_AND_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = 1;
                    warning("a integer AND a integer is always true");
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = 1;
                    warning("a float AND a float is always true");
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    result.bool_val = 1;
                    warning("a string AND a string is always true");
                    _expr_push(&result);
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val && right.bool_val);
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_OR_OPERATOR:
            switch(apparent_type) {
                case EXP_INT:
                    result.bool_val = 1;
                    warning("a integer OR a integer is always true");
                    _expr_push(&result);
                    break;

                case EXP_FLOAT:
                    result.bool_val = 1;
                    warning("a float OR a float is always true");
                    _expr_push(&result);
                    break;

                case EXP_STRING:
                    result.bool_val = 1;
                    warning("a string OR a string is always true");
                    break;

                case EXP_BOOL:
                    result.bool_val = (left.bool_val || right.bool_val);
                    _expr_push(&result);
                    break;

                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        default:
            fatal_error("unknown operator in validate magnitude (parser error)");
    }
    return retv;
}

