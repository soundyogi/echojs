
#ifndef _ejs_ops_h
#define _ejs_ops_h

#include "ejs.h"
#include "ejs-object.h"

EJSValue* _ejs_op_not (EJSValue* exp);
EJSValue* _ejs_op_typeof (EJSValue* exp);
EJSValue* _ejs_op_delete (EJSValue* obj, EJSValue* prop);
EJSValue* _ejs_op_add (EJSValue* lhs, EJSValue* rhs);
EJSValue* _ejs_op_lt (EJSValue* lhs, EJSValue* rhs);
EJSValue* _ejs_op_le (EJSValue* lhs, EJSValue* rhs);
EJSValue* _ejs_op_sub (EJSValue* lhs, EJSValue* rhs);
EJSValue* _ejs_op_strict_eq (EJSValue* lhs, EJSValue* rhs);
EJSValue* _ejs_op_eq (EJSValue* lhs, EJSValue* rhs);

EJSBool _ejs_truthy (EJSValue* val);

extern EJSValue* _ejs_print;
extern EJSValue* _ejs_print_impl (EJSValue* env, EJSValue* _this, int argc, EJSValue **args);

#endif // _ejs_ops_h