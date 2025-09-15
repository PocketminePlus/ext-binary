#ifndef LIMITS_H
#define LIMITS_H

extern "C" {
#include "php.h"
}

extern zend_class_entry* limits_ce;

// Constants that will be registered
#define UINT8_MAX_VAL 0xff
#define INT8_MIN_VAL (-0x7f - 1)
#define INT8_MAX_VAL 0x7f

#define UINT16_MAX_VAL 0xffff
#define INT16_MIN_VAL (-0x7fff - 1)
#define INT16_MAX_VAL 0x7fff

#define UINT32_MAX_VAL 0xffffffff
#define INT32_MIN_VAL (-0x7fffffff - 1)
#define INT32_MAX_VAL 0x7fffffff

#define UINT64_MAX_VAL 0xffffffffffffffff
#define INT64_MIN_VAL (-0x7fffffffffffffff - 1)
#define INT64_MAX_VAL 0x7fffffffffffffff

// Function declarations
extern "C" void init_class_Limits();

#endif // LIMITS_H
