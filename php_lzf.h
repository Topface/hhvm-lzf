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

  $Id: php_lzf.h 326548 2012-07-08 16:47:42Z felipe $
*/

#ifndef PHP_LZF_H
#define PHP_LZF_H

extern zend_module_entry lzf_module_entry;
#define phpext_lzf_ptr &lzf_module_entry

#define PHP_LZF_VERSION "1.6.2"

#ifdef PHP_WIN32
#define PHP_LZF_API __declspec(dllexport)
#else
#define PHP_LZF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define LZF_MARGIN	128

PHP_MINFO_FUNCTION(lzf);
PHP_MINIT_FUNCTION(lzf);
PHP_MSHUTDOWN_FUNCTION(lzf);

PHP_FUNCTION(lzf_compress);
PHP_FUNCTION(lzf_decompress);
PHP_FUNCTION(lzf_optimized_for);

#endif	/* PHP_LZF_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
