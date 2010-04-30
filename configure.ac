#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([luxcmd], [0.0.1], [SumiTomohiko@neko-daisuki.ddo.jp])
AM_INIT_AUTOMAKE([dist-bzip2])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([include/luxcmd/config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([lux], [Lux::DocumentConfigParser::parse])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

# vim: tabstop=2 shiftwidth=2 expandtab softtabstop=2
