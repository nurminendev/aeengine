#!/bin/sh

test -e Makefile && make allclean
aclocal && autoheader && autoconf
