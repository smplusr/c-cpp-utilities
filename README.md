# auto-inapp-recompiler

This header file is a debug utility that aid any kind of project to be recompiled once closed.
The utility by itself is entended to be used for debug builds only.

In order to initialyse it, 4 parameters must be defined:
AUTO_RECOMPILE: 	used to compile and then process the utility.
RECOMPILE_HEADERS: 	for calling the compilation of the extra "header" bin.
SOURCE_PATH: 		the path to the "source" bin.
HEADER_PATH:		the path to the "header" bin.

The paths must lead to a (chosen extension and named) file that will feed a system() function
and parse all the line as OS speecific argument. 

This auto-recompile utility supports C and C++ projects, 
it must be included in the main source file in order to work properly.
All the macros defined in this file could be used inside the main application.
