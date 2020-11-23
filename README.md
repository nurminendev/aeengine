# Old/archived codebase

**This codebase is old/deprecated and probably would need updating to run today**. It is here for archival/nostalgia purposes.

# AE Engine

https://aeengine.sourceforge.net/

AE Engine is a free 3D Engine. It uses OpenGL for graphics 
rendering and SDL to interface with the operating system.
Its main goal is to be fast, flexible and easy to use.


# Compiling & Installing

See the INSTALL file that comes withing the package.


# Documentation & Getting started

Online:
  - http://aeengine.sourceforge.net/documentation.php

Offline:
  - Under the "docs" directory in the AE source tree.
  - docs/pubapi/ - Public API reference

Online documentation can be found at the AE homepage at
http://aeengine.sourceforge.net/documentation.php. The
same documentation can be found from the AE source tree
under the "docs" directory. However, if you want to be
sure you are reading the latest and greatest of the docs,
be sure to check the online version.


# Support & Getting help

There are several ways you can obtain support in AE related
matters.

One (and probably you should do this anyway even if you don't
have any problems) is to subscribe to the AE mailing-list. See
below under "Mailing-lists" for more information and
instructions on how to subscribe.

Another way to obtain support is to mail one of the AE
developers directly. You can find the developers' email-
addresses from the AE web-page at
http://aeengine.sourceforge.net/team.php. The list is not
available here because it might change, and updating all the
READMEs is much more painful than just updating the web-page.

Note that the mailing-list should be your primary source of
support, because that way you'll help everybody instead of only
yourself.


# Reporting bugs:

You can report bugs to riku@nurminen.dev. Please remember to
be as detailed as possible and try to describe the bug as well
as you can and do include all relevant information.

If the bug is a crash, ie. AE causes a segfault, then please
recompile AE with debug mode on (./configure --enable-debug),
and see if the problem persists. If it still happens, go to a
debugger and get a "backtrace" of the crash and include that
in the email. Also include your operating system, your video
card specs and the AE version in question.

Here's an example of a such crash situation on a GNU/Linux
system using the GNU debugger (gdb). At the end there's also 
a boiler-plate email message you could use when reporting a bug:

```
# ./aetest
...
Fatal signal: Segmentation Fault (SDL Parachute Deployed)
# ./configure --enable-debug
# make
# gdb ./aetest
...
This GDB was configured as "i386-linux"...
(gdb) run
...
Program received signal SIGSEGV, Segmentation fault.
[Switching to Thread 16384 (LWP 26032)]
0x0804a8b3 in aeTest::Initialize() (this=0x805fd60) at aetest/main.cpp:248
248             ogro->SetOrigin(aeVector3(380.0, -120.0, 505.0));
(gdb) backtrace
#0  0x0804a8b3 in aeTest::Initialize() (this=0x805fd60) at aetest/main.cpp:248
#1  0x0804af9f in main (argc=1, argv=0xbffff9c4) at aetest/main.cpp:288
(gdb) quit
```

```
To: ae-bugs@madqon.org
...

<List your operating system, graphics-card, and the AE version you
are using.>

<Describe the problem, be as detailed as possible. If it's a crash
situation, list a chunk of code from around the line that causes the
crash.>

gdb backtrace:

rogram received signal SIGSEGV, Segmentation fault.
[Switching to Thread 16384 (LWP 26032)]
0x0804a8b3 in aeTest::Initialize() (this=0x805fd60) at aetest/main.cpp:248
248             ogro->SetOrigin(aeVector3(380.0, -120.0, 505.0));
(gdb) backtrace
#0  0x0804a8b3 in aeTest::Initialize() (this=0x805fd60) at aetest/main.cpp:248
#1  0x0804af9f in main (argc=1, argv=0xbffff9c4) at aetest/main.cpp:288
```

# Mailing-lists

Here are the AE mailing-lists. If you are a user of AE you
should atleast subscribe to the ae-main list.

**aeengine-announce (aeengine-announce@lists.sourceforge.net)**

A moderated, very low-traffic list dedicated to important announcements about AE.

Subscribe/Unsubscribe: http://lists.sourceforge.net/mailman/listinfo/aeengine-announce
Archives: http://sourceforge.net/mailarchive/forum.php?forum=aeengine-announce

**aeengine-devel (aeengine-devel@lists.sourceforge.net)**

A developers' list.

Subscribe/Unsubscribe: http://lists.sourceforge.net/mailman/listinfo/aeengine-devel
Archives: http://sourceforge.net/mailarchive/forum.php?forum=aeengine-devel

**aeengine-main (aeengine-main@lists.sourceforge.net)**

General discussion list.

Subscribe/Unsubscribe: http://lists.sourceforge.net/mailman/listinfo/aeengine-main
Archives: http://sourceforge.net/mailarchive/forum.php?forum=aeengine-main


# URLs

AE Engine homepage: http://aeengine.sourceforge.net

Sourceforge project page: http://www.sourceforge.net/projects/aeengine/
