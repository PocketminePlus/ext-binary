#ifndef PHP_BINARY_H
# define PHP_BINARY_H

extern zend_module_entry binary_module_entry;
# define phpext_binary_ptr &binary_module_entry

# define PHP_BINARY_VERSION "1.0.0"
# define PHP_BINARY_AUTHOR "xsuperr"
# define PHP_BINARY_DESCRIPTION "High-Performance Binary Utils Extension"

# if defined(ZTS) && defined(COMPILE_DL_BINARY)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

// Forward declarations
extern zend_class_entry* binary_data_exception_ce;
extern zend_class_entry* binary_ce;
extern zend_class_entry* binary_stream_ce;
extern zend_class_entry* limits_ce;

// Function declarations
void init_class_Binary();
void init_class_BinaryStream();
void init_class_BinaryDataException();
void init_class_Limits();

#endif	/* PHP_BINARY_H */
