# Ensure we have the correct version of autoconf running and initialise it.
AC_PREREQ([2.61])
AC_INIT(libease, 0.0.6, libease@stroppytux.net, ,http://www.stroppytux.net/projects/libease/)
AM_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])

# Set some information about the headers and makefiles.
AC_CONFIG_SRCDIR([src/ease.h])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

# Checks for programs.
AM_INIT_AUTOMAKE
AC_PROG_CC

# Check for all the header files we need.
AC_CHECK_HEADERS([stdio.h stdarg.h stdlib.h],,AC_MSG_ERROR([required header file missing]))
AC_HEADER_STDC

AC_OUTPUT

