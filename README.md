ks0108.X
========

Project created to easily manage the LCD controller: ks0108 (Samsung, without characters ROM).

The `pinmask.h` is created for work with PIC-32 PINGUINO. But it can be easily adapted to any other development board due to it's structure.

In the near future I will document all functions and I'll create a valid readme.

At the current state, the main program will produce 8 straight lines, 1 px wide. It's only to demostrate how to use some functions.

Conventions
===========

Macros begin with `__NAME`.
Internal variable and functions begin with `_name`
Any public function begin with `name`
