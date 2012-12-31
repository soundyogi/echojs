/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#include <assert.h>

#include "ejs-value.h"
#include "ejs-regexp.h"
#include "ejs-function.h"

static ejsval _ejs_regexp_specop_get (ejsval obj, ejsval propertyName, EJSBool isCStr);
static ejsval _ejs_regexp_specop_get_own_property (ejsval obj, ejsval propertyName);
static ejsval _ejs_regexp_specop_get_property (ejsval obj, ejsval propertyName);
static void      _ejs_regexp_specop_put (ejsval obj, ejsval propertyName, ejsval val, EJSBool flag);
static EJSBool   _ejs_regexp_specop_can_put (ejsval obj, ejsval propertyName);
static EJSBool   _ejs_regexp_specop_has_property (ejsval obj, ejsval propertyName);
static EJSBool   _ejs_regexp_specop_delete (ejsval obj, ejsval propertyName, EJSBool flag);
static ejsval _ejs_regexp_specop_default_value (ejsval obj, const char *hint);
static void      _ejs_regexp_specop_define_own_property (ejsval obj, ejsval propertyName, ejsval propertyDescriptor, EJSBool flag);
static void      _ejs_regexp_specop_finalize (EJSObject* obj);
static void      _ejs_regexp_specop_scan (EJSObject* obj, EJSValueFunc scan_func);

EJSSpecOps _ejs_regexp_specops = {
    "RegExp",
    _ejs_regexp_specop_get,
    _ejs_regexp_specop_get_own_property,
    _ejs_regexp_specop_get_property,
    _ejs_regexp_specop_put,
    _ejs_regexp_specop_can_put,
    _ejs_regexp_specop_has_property,
    _ejs_regexp_specop_delete,
    _ejs_regexp_specop_default_value,
    _ejs_regexp_specop_define_own_property,
    _ejs_regexp_specop_finalize,
    _ejs_regexp_specop_scan
};

EJSObject* _ejs_regexp_alloc_instance()
{
    return (EJSObject*)_ejs_gc_new(EJSRegexp);
}

ejsval
_ejs_regexp_new_utf8 (const char* str)
{
    int str_len = strlen(str);
    size_t value_size = sizeof (EJSRegexp) + str_len;

    EJSRegexp* rv = (EJSRegexp*)_ejs_gc_alloc (value_size, EJS_TRUE);

    _ejs_init_object ((EJSObject*)rv, _ejs_Regexp_proto, &_ejs_regexp_specops);
    ((EJSObject*)rv)->ops = &_ejs_regexp_specops;

    rv->pattern_len = str_len;
    rv->pattern = strdup(str);

    return OBJECT_TO_EJSVAL((EJSObject*)rv);
}

ejsval _ejs_Regexp;
ejsval _ejs_Regexp_proto;

static ejsval
_ejs_Regexp_impl (ejsval env, ejsval _this, int argc, ejsval *args)
{
    if (EJSVAL_IS_UNDEFINED(_this)) {
        // called as a function
        printf ("called Regexp() as a function!\n");
        return _ejs_object_new(_ejs_Regexp_proto);
    }
    else {
        // called as a constructor
        printf ("called Regexp() as a constructor!\n");
        return _this;
    }
}

static ejsval
_ejs_Regexp_prototype_exec (ejsval env, ejsval _this, int argc, ejsval *args)
{
    NOT_IMPLEMENTED();
}

static ejsval
_ejs_Regexp_prototype_match (ejsval env, ejsval _this, int argc, ejsval *args)
{
    NOT_IMPLEMENTED();
}

static ejsval
_ejs_Regexp_prototype_test (ejsval env, ejsval _this, int argc, ejsval *args)
{
    NOT_IMPLEMENTED();
}

void
_ejs_regexp_init(ejsval global)
{
    START_SHADOW_STACK_FRAME;

    _ejs_gc_add_named_root (_ejs_Regexp_proto);
    _ejs_Regexp_proto = _ejs_object_new(_ejs_null);

    ADD_STACK_ROOT(ejsval, tmpobj, _ejs_function_new_utf8 (_ejs_null, "RegExp", (EJSClosureFunc)_ejs_Regexp_impl));
    _ejs_Regexp = tmpobj;

    _ejs_object_setprop (_ejs_Regexp,       _ejs_atom_prototype,  _ejs_Regexp_proto);

#define OBJ_METHOD(x) EJS_MACRO_START ADD_STACK_ROOT(ejsval, funcname, _ejs_string_new_utf8(#x)); ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new (_ejs_null, funcname, (EJSClosureFunc)_ejs_Regexp_##x)); _ejs_object_setprop (_ejs_Regexp, funcname, tmpfunc); EJS_MACRO_END
#define PROTO_METHOD(x) EJS_MACRO_START ADD_STACK_ROOT(ejsval, funcname, _ejs_string_new_utf8(#x)); ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new (_ejs_null, funcname, (EJSClosureFunc)_ejs_Regexp_prototype_##x)); _ejs_object_setprop (_ejs_Regexp_proto, funcname, tmpfunc); EJS_MACRO_END

    PROTO_METHOD(exec);
    PROTO_METHOD(match);
    PROTO_METHOD(test);

#undef OBJ_METHOD
#undef PROTO_METHOD

    _ejs_object_setprop_utf8 (global, "RegExp", _ejs_Regexp);

    END_SHADOW_STACK_FRAME;
}


static ejsval
_ejs_regexp_specop_get (ejsval obj, ejsval propertyName, EJSBool isCStr)
{
    return _ejs_object_specops.get (obj, propertyName, isCStr);
}

static ejsval
_ejs_regexp_specop_get_own_property (ejsval obj, ejsval propertyName)
{
    return _ejs_object_specops.get_own_property (obj, propertyName);
}

static ejsval
_ejs_regexp_specop_get_property (ejsval obj, ejsval propertyName)
{
    return _ejs_object_specops.get_property (obj, propertyName);
}

static void
_ejs_regexp_specop_put (ejsval obj, ejsval propertyName, ejsval val, EJSBool flag)
{
    _ejs_object_specops.put (obj, propertyName, val, flag);
}

static EJSBool
_ejs_regexp_specop_can_put (ejsval obj, ejsval propertyName)
{
    return _ejs_object_specops.can_put (obj, propertyName);
}

static EJSBool
_ejs_regexp_specop_has_property (ejsval obj, ejsval propertyName)
{
    return _ejs_object_specops.has_property (obj, propertyName);
}

static EJSBool
_ejs_regexp_specop_delete (ejsval obj, ejsval propertyName, EJSBool flag)
{
    return _ejs_object_specops._delete (obj, propertyName, flag);
}

static ejsval
_ejs_regexp_specop_default_value (ejsval obj, const char *hint)
{
    return _ejs_object_specops.default_value (obj, hint);
}

static void
_ejs_regexp_specop_define_own_property (ejsval obj, ejsval propertyName, ejsval propertyDescriptor, EJSBool flag)
{
    _ejs_object_specops.define_own_property (obj, propertyName, propertyDescriptor, flag);
}

static void
_ejs_regexp_specop_finalize (EJSObject* obj)
{
    _ejs_object_specops.finalize (obj);
}

static void
_ejs_regexp_specop_scan (EJSObject* obj, EJSValueFunc scan_func)
{
    _ejs_object_specops.scan (obj, scan_func);
}
