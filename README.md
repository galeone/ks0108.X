ks0108.X
========

Project created to easily manage the LCD controller: ks0108 (Samsung, without characters ROM).

The `pinmask.h` is created to work with PIC-32 PINGUINO. But it can be easily adapted to any other development board due to its structure.

The code is well documented, so the only things to know are in which files we have to look.
The main clock time is setup in active_delay.c file, with `#pragma` directives.

Library functions are defined in ks0108.h, and any function or macro is described.

At the current state, the main program will produce 8 straight lines, 1 px wide. It's only to demonstrate how to use some functions.

Usage
=====
It's a library. Build it and enjoy.

Learning by examples
====================
At the current state of art, we got only one example that includes pretty much any function useful for a library usage and not for a contributor.

Remember: to use libraries in MPLABX IDE, you have to include the archive library that you find in `dist/default/production/`, and add root path of this project to your compiler include path (to *.h)

Looking at `samples/main.X/main.c` for a working example).

The main program do the following steps:
1. Configures the board timer (b type, active delay, not asynchronous) with the appropriate SFRs.
2. Initializes the ks0108 library with the appropriate SFRs.
3. Uses raw methods to draw 8 straight lines, 1 px wide.
4. Wait a second
5. Turns on only left side of display and turns off the right one [the right display will not show anything, while the left one will show the 8 lines]
6. Wait a second
7. Does the step 5 for the right display
8. Wait, turns on both display and clears the screen
9. Use the function ks0108_write_string, to easily write strings to the lcd, without worrying about nothing

Contribute
==========
Wanna contribute? Feel free to do it. But please, respect these simple...

Conventions
===========
Macros begins with `__NAME`. If macros can be functions (I mean that it is a block `{}` of code) , use `extern inline returntype __NAME`

Internal variables and functions begins with `_name`

Any public function begins with `name`
