#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([solver], [0.1], [yuege@ices.utexas.edu])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/main.c])

AM_INIT_AUTOMAKE

# Paths
AX_PATH_MASA([0.30],[yes])
AX_PATH_GRVY([0.32],[yes])

# Checks for programs.
AC_PROG_CC

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_OUTPUT(Makefile src/Makefile test/Makefile)
