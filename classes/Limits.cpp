#include "Limits.h"

extern "C" {
#include "php.h"
#include "zend_exceptions.h"
#include "ext-binary_arginfo.h"
}

// Class entry for Limits
zend_class_entry* limits_ce;

extern "C" {

// Private constructor to prevent instantiation
PHP_METHOD(Limits, __construct) {
    zend_throw_error(NULL, "Cannot instantiate final class Limits");
}

// Limits class methods using generated arginfo
static const zend_function_entry limits_methods[] = {
    PHP_ME(Limits, __construct, arginfo_class_Limits___construct, ZEND_ACC_PRIVATE | ZEND_ACC_CTOR)
    PHP_FE_END
};

} // extern "C"

// Class initialization function
extern "C" void init_class_Limits() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Limits", limits_methods);
    limits_ce = zend_register_internal_class(&ce);

    // Make the class final (cannot be extended)
    limits_ce->ce_flags |= ZEND_ACC_FINAL;

    zend_declare_class_constant_long(limits_ce, "UINT8_MAX", sizeof("UINT8_MAX") - 1, 0xff);
    zend_declare_class_constant_long(limits_ce, "INT8_MIN", sizeof("INT8_MIN") - 1, -0x7f - 1);
    zend_declare_class_constant_long(limits_ce, "INT8_MAX", sizeof("INT8_MAX") - 1, 0x7f);

    zend_declare_class_constant_long(limits_ce, "UINT16_MAX", sizeof("UINT16_MAX") - 1, 0xffff);
    zend_declare_class_constant_long(limits_ce, "INT16_MIN", sizeof("INT16_MIN") - 1, -0x7fff - 1);
    zend_declare_class_constant_long(limits_ce, "INT16_MAX", sizeof("INT16_MAX") - 1, 0x7fff);

    zend_declare_class_constant_long(limits_ce, "UINT32_MAX", sizeof("UINT32_MAX") - 1, 0xffffffff);
    zend_declare_class_constant_long(limits_ce, "INT32_MIN", sizeof("INT32_MIN") - 1, -0x7fffffff - 1);
    zend_declare_class_constant_long(limits_ce, "INT32_MAX", sizeof("INT32_MAX") - 1, 0x7fffffff);

    // UINT64_MAX: PHP converts 0xffffffffffffffff to double, so we must use double too
    zend_declare_class_constant_double(limits_ce, "UINT64_MAX", sizeof("UINT64_MAX") - 1, (double)0xffffffffffffffffULL);
    zend_declare_class_constant_long(limits_ce, "INT64_MIN", sizeof("INT64_MIN") - 1, -0x7fffffffffffffff - 1);
    zend_declare_class_constant_long(limits_ce, "INT64_MAX", sizeof("INT64_MAX") - 1, 0x7fffffffffffffff);
}
