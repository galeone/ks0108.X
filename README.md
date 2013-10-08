ks0108.X
========

Project created to easily manage the LCD controller: ks0108 (Samsung, without characters ROM).

The `pinmask.h` is created to work with PIC-32 PINGUINO. But it can be easily adapted to any other development board due to its structure.

In the near future I will document all functions and I'll create a valid readme.

At the current state, the main program will produce 8 straight lines, 1 px wide. It's only to demostrate how to use some functions.

Conventions
===========

Macros begins with `__NAME`. If macros can be functions (I mean that it is a block `{}` of code) , use `extern inline returntype __NAME`

Internal variables and functions begins with `_name`

Any public function begins with `name`
