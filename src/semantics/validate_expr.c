
#include "common.h"
#include <math.h>

_expr_element* validate_stack = NULL;
extern _expr_list* expr_stack;

#ifdef _DEBUGGING
#define _DEBUG_ITEM(e, m) do{ \
        char b[1024]; \
        _stack_item_to_str(e, b, sizeof(b)); \
        _DEBUG(5, "%s %s", m, b); \
    }while(0)
static inline const char* _stack_item_to_str(_expr_element* elem, char* buffer, size_t bsize) {

    switch(elem->type) {
        case EXP_FLOAT:
            snprintf(buffer, bsize, "%s = %g", EXPR_TYPE_TO_STR(elem->type), elem->fpnum);
            break;
        case EXP_INT:
            snprintf(buffer, bsize, "%s = %lld", EXPR_TYPE_TO_STR(elem->type), elem->intnum);
            break;
        case EXP_STRING:
            snprintf(buffer, bsize, "%s = %s", EXPR_TYPE_TO_STR(elem->type), elem->str);
            break;
        case EXP_BOOL:
            snprintf(buffer, bsize, "%s = %s", EXPR_TYPE_TO_STR(elem->type), (elem->bool_val)? "TRUE": "FALSE");
            break;
        default:
            snprintf(buffer, bsize, "%s", EXPR_TYPE_TO_STR(elem->type));
    }
    return buffer;
}
#else
#define _DEBUG_ITEM(e, m)
#endif

static inline void _push(_expr_element* elem) {

    _DEBUG_ITEM(elem, "        push:");
    _expr_element* nele = CALLOC(1, sizeof(_expr_element));
    memcpy(nele, elem, sizeof(_expr_element));
    nele->next = validate_stack;
    validate_stack = nele;
}

static inline int _pop(_expr_element* elem) {

    if(validate_stack != NULL) {
        _DEBUG_ITEM(validate_stack, "        pop:");
        _expr_element* oele = validate_stack;
        validate_stack = oele->next;
        memcpy(elem, oele, sizeof(_expr_element));
        FREE(oele);
        return 1;
    }

    return 0; // stack is empty
}

static inline _expr_element* _peek(void) {
    return validate_stack;
}

/**
 * @brief This function validates the left and right factors for a magnitude
 * comparison. Returns 1 for valid comparison and 0 for invalid.
 *
 */
static int _magnitude_lr(_expr_element* left, _expr_element* right) {

    int retv = 0; // pessimestic

    switch(left->type) {
        case EXP_FLOAT:
            switch(right->type) {
                case EXP_FLOAT:
                    retv = EXP_FLOAT;
                    break;
                case EXP_STRING:
                    syntax("magnitude compare on a number and a string is invalid. (use a cast)");
                    break;
                case EXP_BOOL:
                    syntax("magnitude compare on number and bool is invalid. (use a cast)");
                    break;
            }
            break;
        case EXP_STRING:
            switch(right->type) {
                case EXP_STRING:
                    retv = EXP_STRING;
                    break;
                case EXP_FLOAT:
                    syntax("magnitude compare on a number and a string is invalid. (use a cast)");
                    break;
                case EXP_BOOL:
                    syntax("magnitude compare on string and bool is invalid. (use a cast)");
                    break;
            }
            break;
        case EXP_BOOL:
            switch(right->type) {
                case EXP_BOOL:
                    retv = EXP_BOOL;
                    break;
                case EXP_STRING:
                    syntax("magnitude compare on string and bool is invalid. (use a cast)");
                    break;
                case EXP_FLOAT:
                    syntax("magnitude compare on number and bool is invalid. (use a cast)");
                    break;
            }
            break;
    }
    return retv;
}

/**
 * @brief This function validates that the left and the right factors are
 * compatible. Return the likely result of the operation. Return 0 if there
 * is an error.
 */
static int _arith_lr(_expr_element* left, _expr_element* right) {

    int retv = 0; // pessimestic

    switch(left->type) {
        case EXP_FLOAT:
            switch(right->type) {
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
                case EXP_BOOL:
                    retv = EXP_BOOL;
                    break;
                case EXP_STRING:
                    syntax("arithmetic operation on string and bool is invalid. (use a cast)");
                    break;
                case EXP_FLOAT:
                    syntax("arithmetic operation on number and bool is invalid. (use a cast)");
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
static int _comparison(int op) {

    _MARK(5);
    _expr_element left;
    _expr_element right;
    _expr_element result;
    int apparent_type;  // number, bool, or string
    int retv = 0;

    if(!_pop(&right))
        fatal_error("expression stack underflow on right operand (parser error)");
    if(!_pop(&left))
        fatal_error("expression stack underflow on left operand (parser error)");

    if(0 == (apparent_type = _magnitude_lr(&left, &right))) {
        _DEBUG(5, "expr_error: %s -> %s = %s",
               EXPR_TYPE_TO_STR(left.type),
               EXPR_TYPE_TO_STR(right.type),
               EXPR_TYPE_TO_STR(apparent_type));
        return EXP_ERROR;
    }

    memset(&result, 0, sizeof(_expr_element));
    result.type = EXP_BOOL;

    switch(op) {
        case EXP_EQU_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum == right.fpnum);
                    _push(&result);
                    warning("comparing two numbers for equality is risky");
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
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;
        case EXP_NEQU_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum != right.fpnum);
                    _push(&result);
                    warning("comparing two numbers for inequality is risky");
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
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;
        case EXP_LT_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum < right.fpnum);
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.type = EXP_ERROR;
                    syntax("comparing strings for other then equality does not make sense.");
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val < right.bool_val);
                    _push(&result);
                    warning("comparing bools for other than equality may yield unexpected result");
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;
        case EXP_GT_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum > right.fpnum);
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.type = EXP_ERROR;
                    syntax("comparing strings for other then equality does not make sense.");
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val > right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;
        case EXP_GTE_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum >= right.fpnum);
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.type = EXP_ERROR;
                    syntax("comparing strings for other then equality does not make sense.");
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val >= right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;
        case EXP_LTE_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = (left.fpnum <= right.fpnum);
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.type = EXP_ERROR;
                    syntax("comparing strings for other then equality does not make sense.");
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val <= right.bool_val);
                    warning("comparing bools for other than equality may yield unexpected result");
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_AND_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = 1;
                    warning("a number AND a number is always true");
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.bool_val = 1;
                    warning("a string AND a string is always true");
                    _push(&result);
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val && right.bool_val);
                    _push(&result);
                    break;
                default:
                    fatal_error("unknown expression type in validate magnitude compare. (parser error)");
            }
            break;

        case EXP_OR_OPERATOR:
            switch(apparent_type) {
                case EXP_FLOAT:
                    result.bool_val = 1;
                    warning("a number OR a number is always true");
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.bool_val = 1;
                    warning("a string OR a string is always true");
                    break;
                case EXP_BOOL:
                    result.bool_val = (left.bool_val || right.bool_val);
                    _push(&result);
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

/**
 * @brief This function validates an arithmetic operation.
 *
 * TODO: add logic to see if the result is a valid type
 */
static int _arithmetic(int op) { //, int type) {

    _MARK(5);
    _expr_element left;
    _expr_element right;
    _expr_element result;
    int apparent_type;  // number, bool, or string
    int retv = 0;

    if(!_pop(&right))
        fatal_error("expression stack underflow on right operand (parser error)");
    if(!_pop(&left))
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
                case EXP_FLOAT:
                    result.fpnum = left.fpnum + right.fpnum;
                    _push(&result);
                    break;
                case EXP_STRING:
                    result.type = EXP_STRING;
                    result.str = alloc_cat(left.str, right.str);
                    _push(&result);
                    FREE(right.str);
                    FREE(left.str);
                    break;
                default:
                    syntax("cannot perform addition operation");
                    retv = 1;
                    break;
            }
            break;

        case EXP_SUB_OPERATOR:
            if(apparent_type != EXP_FLOAT) {
                syntax("cannot perform subtraction operation");
                retv = 1;
            }
            result.fpnum = left.fpnum - right.fpnum;
            _push(&result);
            break;

        case EXP_MUL_OPERATOR:
            if(apparent_type != EXP_FLOAT) {
                syntax("cannot perform multiplication operation");
                retv = 1;
            }
            result.fpnum = left.fpnum * right.fpnum;
            _push(&result);
            break;

        case EXP_DIV_OPERATOR:
            if(apparent_type != EXP_FLOAT) {
                syntax("cannot perform division operation");
                retv = 1;
            }

            if(right.fpnum == 0.0) {
                syntax("right side of division cannot be zero.");
                fatal_error("divide by zero error");
            }
            result.fpnum = left.fpnum / right.fpnum;
            _push(&result);
            break;

        case EXP_MOD_OPERATOR:
            if(apparent_type != EXP_FLOAT) {
                syntax("cannot perform modulo operation");
                retv = 1;
            }

            if(right.fpnum == 0.0) {
                syntax("right side of division cannot be zero.");
                fatal_error("divide by zero error");
            }
            result.fpnum = remainder(left.fpnum, right.fpnum);
            _push(&result);
            break;

        default:
            fatal_error("unknown operator in validate aritmetic (parser error)");
    }
    return retv;
}

/**
 * @brief This function makes sure that the expression can be solved from
 * a semantic point of view. For example, it does not make any sense to add
 * a number to a string without a cast.
 */
void validate_expression(void) {
    _TRACE("validating the expression");

    _expr_element* crnt;

    _DEBUG(5, "expression queue:");
    for(crnt = expr_stack->first; crnt != NULL; crnt = crnt->next) {

        switch(crnt->type) {
            // These are not so much types as they are actions that have to
            // be carried out for the expression to make sense.
            case EXP_FLOAT:
                // just push it on the eval stack. The expression can be
                // arithmetic or boolean. All of the operands should match
                // types or a warning is produced.
                _DEBUG_ITEM(crnt, "    ");
                _push(crnt);
                break;

            case EXP_STRING:
                // The expression must be boolean or addition and all
                // of the operands must be strings.
                _DEBUG_ITEM(crnt, "    ");
                _push(crnt);
                break;

            case EXP_BOOL:
                // The expression must be boolean. Operands can be any type,
                // but warnings are generated when they are not boolean.
                _DEBUG_ITEM(crnt, "    ");
                _push(crnt);
                break;

            case EXP_SYMBOL: {
                    // a symbol can be any type and so it needs to be looked
                    // up before the expression can be solved.
                    _DEBUG_ITEM(crnt, "    ");

                    // For development and debugging all symbols are numbers with a value of 5.0.
                    _expr_element tmp;
                    memset(&tmp, 0, sizeof(_expr_element));
                    tmp.type = EXP_FLOAT;
                    tmp.fpnum = 5.0;
                    _push(&tmp);
                }
                break;

            case EXP_SUBSCRIPTED:
                // a subscripted type is a memory of an array or a hash. It
                // needs to be evaluated before the expression can be solved.
                _DEBUG_ITEM(crnt, "    ");

                fatal_error("subscripted variables are not supported (yet)");
                break;

                // Operations on all of the operators except add must be numbers. If an
                // either one of the operands is not a number, then a syntax error is
                // is published. In the case of the add operator, strings may be added.
            case EXP_ADD_OPERATOR:
            case EXP_SUB_OPERATOR:
            case EXP_MUL_OPERATOR:
            case EXP_DIV_OPERATOR:
            case EXP_MOD_OPERATOR:
                _DEBUG_ITEM(crnt, "    ");
                _arithmetic(crnt->type); //, crnt->apparent_type);
                break;

                // For boolean operations, Only values of the same type can be compared.
                // When two values of different types are compared, then the result is
                // always false. Since all numbers are double precision floats, they cannot
                // be taken to actually be zero, comparing two numbers as greater or equal
                // is the same as comparing for greater. Comparing two floats for equal is
                // not a valid comparison in most cases. When comparing two floats for equal,
                // the fractional part is truncated.
            case EXP_EQU_OPERATOR:
            case EXP_NEQU_OPERATOR:
            case EXP_LT_OPERATOR:
            case EXP_GT_OPERATOR:
            case EXP_GTE_OPERATOR:
            case EXP_LTE_OPERATOR:
            case EXP_AND_OPERATOR:
            case EXP_OR_OPERATOR:
                _DEBUG_ITEM(crnt, "    ");
                _comparison(crnt->type);
                break;


                // These operators are unary and right associative. They accept exactly one
                // operand.
            case EXP_NOT_OPERATOR: {
                // The operand must be boolean. Other types produce a syntax error.
                    _DEBUG_ITEM(crnt, "    ");
                    _expr_element val;
                    _expr_element res;

                    if(!_pop(&val))
                        fatal_error("expression stack underflow for not operator (parser error)");

                    memset(&res, 0, sizeof(_expr_element));

                    switch(val.type) {
                        case EXP_FLOAT:
                            syntax("cannot perform NOT on a number. (use unary operator)");
                            res.type = EXP_ERROR;
                            _push(&res);
                            break;

                        case EXP_STRING:
                            syntax("cannot perform NOT on a string. (use unary operator)");
                            res.type = EXP_ERROR;
                            _push(&res);
                            break;

                        case EXP_BOOL:
                            res.type = EXP_BOOL;
                            res.bool_val = (val.bool_val == 0)? 1: 0;
                            _push(&res);
                            break;

                        default:
                            fatal_error("unknown operand type for NOT operator");
                    }
                }
                break;

            case EXP_UNARY_PLUS:
            case EXP_UNARY_MINUS: {
                    // The operand must evaluate to a number.
                    _DEBUG_ITEM(crnt, "    ");
                    _expr_element val;
                    _expr_element res;

                    if(!_pop(&val))
                        fatal_error("expression stack underflow for not operator (parser error)");

                    memset(&res, 0, sizeof(_expr_element));

                    switch(val.type) {
                        case EXP_FLOAT:
                            res.type = EXP_FLOAT;
                            if(crnt->type == EXP_UNARY_PLUS)
                                res.fpnum = +val.fpnum;
                            else if(crnt->type == EXP_UNARY_MINUS)
                                res.fpnum = -val.fpnum;
                            _push(&res);
                            break;

                        case EXP_STRING:
                            syntax("cannot unary arithmetic unary operator to a string.");
                            res.type = EXP_ERROR;
                            _push(&res);
                            break;

                        case EXP_BOOL:
                            syntax("cannot unary arithmetic operator to a bool.");
                            res.type = EXP_ERROR;
                            _push(&res);
                            break;

                        default:
                            fatal_error("unknown operand type for NOT operator");
                    }
                }

                break;

            case EXP_CAST:
                // In theory any type can be cast to any other type. The jury is out.
                _DEBUG_ITEM(crnt, "    ");
                break;

            case EXP_CAST_TYPE:
                // In theory any type can be cast to any other type. The jury is out.
                break;

            default:
                break;

        }
    }

    _DEBUG(5, "stack remainders:");
    _expr_element ele;
    while(_pop(&ele)) {}
    clear_expr_flags();
}
