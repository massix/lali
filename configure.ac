AC_PREREQ([2.68])
AC_INIT([lali], [0.7.0dev], [massimo.gengarelli@gmail.com])
AM_INIT_AUTOMAKE

# C++ FTW
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_RANLIB
AC_C_CONST

# Check headers
AC_CHECK_HEADERS([pthread.h arpa/inet.h netdb.h stdint.h stdlib.h string.h strings.h sys/socket.h unistd.h])

# Create header
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_SRCDIR([src/config.h.in])

# Check compiler types
AC_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Check Malloc and stuff
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero memmove memset select socket strcasecmp strdup])

# Output files
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/core/Makefile
  src/web/Makefile
  src/exporters/Makefile
  src/flate/Makefile
  tests/Makefile
  templates/Makefile
  resources/Makefile
  templates/debug_template.html
  resources/lalirc
  tests/config_test.cpp
])

AC_OUTPUT
