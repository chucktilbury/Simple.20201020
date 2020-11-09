
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

void _expr_push(_expr_element* elem) {

    _DEBUG_ITEM(elem, "        push:");
    _expr_element* nele = CALLOC(1, sizeof(_expr_element));
    memcpy(nele, elem, sizeof(_expr_element));
    nele->next = validate_stack;
    validate_stack = nele;
}

int _expr_pop(_expr_element* elem) {

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

_expr_element* _expr_peek(void) {
    return validate_stack;
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
            case EXP_INT:
                _DEBUG_ITEM(crnt, "    ");
                _expr_push(crnt);
                break;

            case EXP_FLOAT:
                // just push it on the eval stack. The expression can be
                // arithmetic or boolean. All of the operands should match
                // types or a warning is produced.
                _DEBUG_ITEM(crnt, "    ");
                _expr_push(crnt);
                break;

            case EXP_STRING:
                // The expression must be boolean or addition and all
                // of the operands must be strings.
                _DEBUG_ITEM(crnt, "    ");
                _expr_push(crnt);
                break;

            case EXP_BOOL:
                // The expression must be boolean. Operands can be any type,
                // but warnings are generated when they are not boolean.
                _DEBUG_ITEM(crnt, "    ");
                _expr_push(crnt);
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
                    _expr_push(&tmp);
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

                    if(!_expr_pop(&val))
                        fatal_error("expression stack underflow for not operator (parser error)");

                    memset(&res, 0, sizeof(_expr_element));

                    switch(val.type) {
                        case EXP_INT:
                            syntax("cannot perform NOT on an integer. (use unary operator)");
                            res.type = EXP_ERROR;
                            _expr_push(&res);
                            break;

                        case EXP_FLOAT:
                            syntax("cannot perform NOT on a float. (use unary operator)");
                            res.type = EXP_ERROR;
                            _expr_push(&res);
                            break;

                        case EXP_STRING:
                            syntax("cannot perform NOT on a string. (use unary operator)");
                            res.type = EXP_ERROR;
                            _expr_push(&res);
                            break;

                        case EXP_BOOL:
                            res.type = EXP_BOOL;
                            res.bool_val = (val.bool_val == 0)? 1: 0;
                            _expr_push(&res);
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

                    if(!_expr_pop(&val))
                        fatal_error("expression stack underflow for not operator (parser error)");

                    memset(&res, 0, sizeof(_expr_element));

                    switch(val.type) {
                        case EXP_INT:
                            res.type = EXP_INT;
                            if(crnt->type == EXP_UNARY_PLUS)
                                res.intnum = +val.intnum;
                            else if(crnt->type == EXP_UNARY_MINUS)
                                res.intnum = -val.intnum;
                            _expr_push(&res);
                            break;

                        case EXP_FLOAT:
                            res.type = EXP_FLOAT;
                            if(crnt->type == EXP_UNARY_PLUS)
                                res.fpnum = +val.fpnum;
                            else if(crnt->type == EXP_UNARY_MINUS)
                                res.fpnum = -val.fpnum;
                            _expr_push(&res);
                            break;

                        case EXP_STRING:
                            syntax("cannot unary arithmetic unary operator to a string.");
                            res.type = EXP_ERROR;
                            _expr_push(&res);
                            break;

                        case EXP_BOOL:
                            syntax("cannot unary arithmetic operator to a bool.");
                            res.type = EXP_ERROR;
                            _expr_push(&res);
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

//             case EXP_CAST_TYPE:
//                 // In theory any type can be cast to any other type. The jury is out.
//                 break;

            default:
                break;

        }
    }

    _DEBUG(5, "stack remainders:");
    _expr_element ele;
    while(_expr_pop(&ele)) {}
    clear_expr_flags();
}
