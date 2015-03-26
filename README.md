# HHVM-LZF-1.6.2

LZF extension to HHVM. Source from [pecl.php.net](http://pecl.php.net/package/lzf). It was edited, so that it could be built with HHVM's [Zend Extension Source Compatibility Layer](https://github.com/facebook/hhvm/tree/master/hphp/runtime/ext_zend_compat).

## Changes compared to the PHP-version

- Commented out undocumented stream filters `lzf.compress`, `lzf.decomplress` (unsupported by ext_zend_compat)
- In lzf_compress(), lzf_decompress() `WRONG_PARAM_COUNT;` -> `return;` (unsupported by ext_zend_compat)
- Added explicit type conversion of results of emalloc(), ecalloc(), erealloc()
- Converted tests to HHVM format

## Building

To build it you'll need to build whole HHVM. Clone this repo to `<HHVM's dir>/hphp/runtime/ext_zend_compat/`, and run
```
cd <HHVM's dir>
cmake .
make -j <num cpus>
sudo make isntall
```

Don't forget to add `hhvm.enable_zend_compat = true` to `php.ini` file.
