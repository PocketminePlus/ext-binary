#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
#include "php_binary.h"
#include "ext/spl/spl_exceptions.h"
}

#include "classes/Binary.h"
#include "classes/BinaryStream.h"
#include "classes/Limits.h"
#include "classes/BinaryDataException.h"

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(binary)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ext-binary", "High-Performance Binary Utils Extension");
	php_info_print_table_row(2, "Version", PHP_BINARY_VERSION);
	php_info_print_table_row(2, "Author", "xsuperr");
	php_info_print_table_row(2, "Description", "C++ implementation of PocketMine BinaryUtils for improved performance");
	php_info_print_table_row(2, "License", "MIT");
	php_info_print_table_row(2, "Homepage", "https://github.com/xsuperr/ext-binary");
	php_info_print_table_row(2, "Status", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(binary)
{
#if defined(ZTS) && defined(COMPILE_DL_BINARY)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

// Global class entry variables
zend_class_entry* binary_data_exception_ce;
zend_class_entry* binary_ce;
zend_class_entry* binary_stream_ce;

PHP_MINIT_FUNCTION(binary) {
	// Initialize exception class first
	init_class_BinaryDataException();

	// Initialize other classes
	init_class_Binary();
	init_class_BinaryStream();
	init_class_Limits();

	return SUCCESS;
}

static const zend_module_dep module_dependencies[] = {
	ZEND_MOD_REQUIRED("spl")
	ZEND_MOD_END
};

/* {{{ binary_module_entry */
zend_module_entry binary_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL, /* ini_entries */
	module_dependencies,
	"binary",					/* Extension name */
	NULL,					/* zend_function_entry */
	PHP_MINIT(binary),			/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(binary),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(binary),			/* PHP_MINFO - Module info */
	PHP_BINARY_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BINARY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
extern "C" {
ZEND_GET_MODULE(binary)
}
#endif
