PHP_ARG_ENABLE([binary],
  [whether to enable ext-binary support],
  [AS_HELP_STRING([--enable-binary],
    [Enable ext-binary high-performance binary utils extension])],
  [no])

if test "$PHP_BINARY" != "no"; then
  PHP_REQUIRE_CXX()

  dnl the 6th parameter here is required for C++ shared extensions
  PHP_NEW_EXTENSION(binary, binary.cpp classes/Binary.cpp classes/BinaryStream.cpp classes/Limits.cpp, $ext_shared,,-std=c++14 -Wall -Werror, yes)
  PHP_ADD_BUILD_DIR($ext_builddir/classes, 1)
fi
