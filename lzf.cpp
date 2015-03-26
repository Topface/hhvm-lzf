/*
+----------------------------------------------------------------------+
| PHP Version 4                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2003 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 2.02 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available at through the world-wide-web at                           |
| http://www.php.net/license/2_02.txt.                                 |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: Marcin Gibula <mg@iceni.pl>                                  |
+----------------------------------------------------------------------+

$Id: lzf.c 326515 2012-07-07 00:36:08Z felipe $
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_lzf.h"

#include "lzf.h"

#ifndef PHP_LZF_ULTRA_FAST
#define PHP_LZF_ULTRA_FAST 1
#endif

/* {{{ lzf_functions[]
*
* Every user visible function must have an entry in lzf_functions[].
*/
zend_function_entry lzf_functions[] = {
	PHP_FE(lzf_compress,		NULL)
	PHP_FE(lzf_decompress,		NULL)
	PHP_FE(lzf_optimized_for,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in lzf_functions[] */
};
/* }}} */

/* {{{ lzf_module_entry
*/
zend_module_entry lzf_module_entry = {
	#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
	#endif
	"lzf",
	lzf_functions,
	PHP_MINIT(lzf),
	PHP_MSHUTDOWN(lzf),
	NULL,
	NULL,
	PHP_MINFO(lzf),
	#if ZEND_MODULE_API_NO >= 20010901
	PHP_LZF_VERSION,
	#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LZF
ZEND_GET_MODULE(lzf)
#endif

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(lzf)
{
    //php_stream_filter_register_factory("lzf.compress", &php_lzf_compress_filter_factory TSRMLS_CC);
    //php_stream_filter_register_factory("lzf.decompress", &php_lzf_decompress_filter_factory TSRMLS_CC);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(lzf)
{
    //php_stream_filter_unregister_factory("lzf.compress" TSRMLS_CC);
    //php_stream_filter_unregister_factory("lzf.decompress" TSRMLS_CC);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(lzf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "lzf support", "enabled");
	php_info_print_table_row(2, "version", PHP_LZF_VERSION);
	/*php_info_print_table_row(2, "lzf API version", LZF_VERSION);*/
	#if PHP_LZF_ULTRA_FAST
	php_info_print_table_row(2, "optimized for", "speed");
	#else
	php_info_print_table_row(2, "optimized for", "compression quality");
	#endif
	php_info_print_table_end();
}
/* }}} */


/* {{{ proto string lzf_compress(string arg)
Return a string compressed with LZF */
PHP_FUNCTION(lzf_compress)
{
	char *retval, *arg = NULL;
	int arg_len, result;

	if (ZEND_NUM_ARGS() != 1 || zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
		//WRONG_PARAM_COUNT;
	}

	retval = (char*) emalloc(arg_len + LZF_MARGIN);
	if (!retval) {
		RETURN_FALSE;
	}

	result = lzf_compress(arg, arg_len, retval, arg_len + LZF_MARGIN);
	if (result == 0) {
		efree(retval);
		RETURN_FALSE;
	}

	retval = (char*) erealloc(retval, result + 1);
	retval[result] = 0;

	RETURN_STRINGL(retval, result, 0);
}
/* }}} */

/* {{{ proto string lzf_decompress(string arg)
Return a string decompressed with LZF */
PHP_FUNCTION(lzf_decompress)
{
	char *arg = NULL;
	int arg_len, result, i = 1;
	char *buffer;
	size_t buffer_size = 1024;

	if (ZEND_NUM_ARGS() != 1 || zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
		//WRONG_PARAM_COUNT;
	}

	buffer = (char*) emalloc(buffer_size);
	if (!buffer) {
		RETURN_FALSE;
	}

	do {
		buffer_size *= i++;
		buffer = (char*) erealloc(buffer, buffer_size);

		result = lzf_decompress(arg, arg_len, buffer, buffer_size);
	} while (result == 0 && errno == E2BIG);

	if (result == 0) {
		if (errno == EINVAL) {
			php_error(E_WARNING, "%s LZF decompression failed, compressed data corrupted", get_active_function_name(TSRMLS_C));
		}

		efree(buffer);
		RETURN_FALSE;
	}

	buffer = (char*) erealloc(buffer, result + 1);
	buffer[result] = 0;

	RETURN_STRINGL(buffer, result, 0);
}
/* }}} */

/* {{{ proto int lzf_optimized_for()
Return 1 if lzf was optimized for speed, 0 for compression */
PHP_FUNCTION(lzf_optimized_for)
{
	RETURN_LONG(PHP_LZF_ULTRA_FAST);
}

/* }}} */

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: noet sw=4 ts=4 fdm=marker
* vim<600: noet sw=4 ts=4
*/

