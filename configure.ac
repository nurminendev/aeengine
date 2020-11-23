#                                               -*- Autoconf -*-
################################################################
#
#  AE Engine autoconf input script
#
#  Copyright (C) 2003 Riku "Rakkis" Nurminen
#
#  Process this file with autoconf to produce a configure script.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
################################################################

AC_INIT(AE Engine, 0.1, riku@nurminen.dev, aeengine)
AC_CONFIG_HEADER(include/config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AC_CHECK_PROG(UNAME, uname, uname)
AC_ARG_ENABLE(debug, [  --enable-debug          build with debug mode on (default OFF)], ae_build_debug=$enableval)

# This isn't used now, but it's there for future purposes.
AC_MSG_CHECKING([system type])
SYSTEM_TYPE=`${UNAME}`
AC_MSG_RESULT($SYSTEM_TYPE)

# Check for AEROOT env var.
AC_MSG_CHECKING([for AEROOT environment variable])
if test -z "$AEROOT"; then
	AC_MSG_RESULT([not set])
	AC_MSG_RESULT([])
	AC_MSG_RESULT([The AEROOT environment variable is not set. In order to run AE Engine you])
	AC_MSG_RESULT([must set this variable to point to the AE source tree (with no trailing slash).])
	AC_MSG_RESULT([])
	AC_MSG_RESULT([Here's an example on how to do this in Bash:])
	AC_MSG_RESULT([])
	AC_MSG_RESULT([		export AEROOT=[$PWD]])
	AC_MSG_RESULT([])
	AC_MSG_RESULT([You might also want to add that line at the end of your ~/.bashrc so it gets set])
	AC_MSG_RESULT([everytime you log into your shell.])
	AC_MSG_RESULT([])
	AC_MSG_RESULT([For more detailed instructions (and how to set it on other shells / OSs) please])
	AC_MSG_RESULT([refer to the AE Engine manual chapter x.x, "Setting the AEROOT environment variable".])
	AC_MSG_RESULT([The AE Engine manual can be found under docs/manual/ in the AE source tree, or])
	AC_MSG_RESULT([online at http://aeengine.sourceforge.net/documentation/manual/])
	AC_MSG_RESULT([])
	AC_MSG_ERROR([AEROOT not set])
else
	AC_MSG_RESULT([[$AEROOT], ok])
fi

# Flags for normal (optimize) build
AE_CFLAGS="-O2 -Wall -fcheck-new -falign-functions -fomit-frame-pointer"

# AE Libs
AELIBS="-laereg -laeengine -laegeom -laegfx -laemm -laesys -laeutil"
AC_SUBST(AELIBS)

if test "$ae_build_debug" = "yes"; then
	# Flags for debug build
	AE_CFLAGS="-g -Wall -fcheck-new -falign-functions"
	AC_DEFINE_UNQUOTED(DEBUG, 1, [Define to 1 to set debug mode on])
else
	AC_DEFINE_UNQUOTED(DEBUG, 0, [Define to 1 to set debug mode on])
fi

# Check for OpenGL
MDL_HAVE_OPENGL

# Check for SDL
AC_PATH_SDL(,,AC_MSG_ERROR([*** SDL not found!]))

# Check for other libs
AC_CHECK_LIB(dl, dlopen)

AC_SUBST(AE_CFLAGS)
CFLAGS="$AE_CFLAGS $GL_CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $GL_LIBS $SDL_LIBS"

# Checks for header files.
AC_CHECK_HEADERS(dlfcn.h)

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
				apps/Makefile
				apps/aetest/Makefile
				src/libs/Makefile
				src/libs/aeengine/Makefile
				src/libs/aegeom/Makefile
				src/libs/aegfx/Makefile
				src/libs/aemm/Makefile
				src/libs/aereg/Makefile
				src/libs/aesys/Makefile
				src/libs/aeutil/Makefile
				src/plugins/Makefile
				src/plugins/aemdlldr/Makefile
				src/plugins/aeterrman/Makefile
				src/plugins/aetxtldr/Makefile])
AC_OUTPUT
AC_MSG_RESULT([])
AC_MSG_RESULT([ Type \"make\" to compile AE Engine])
AC_MSG_RESULT([])
