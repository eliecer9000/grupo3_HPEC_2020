AC_PREREQ([2.69])
AC_INIT([memcheck], [1.0], [eliecer@estudiantec.cr])
AM_INIT_AUTOMAKE
LT_INIT([disable-static])
AC_ENABLE_SHARED
AC_CONFIG_SRCDIR([lib/libmemcheck.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
lib/Makefile
src/Makefile])

AC_OUTPUT
