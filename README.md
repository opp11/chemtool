chemtool
==============================================================================
Small tool for calculating the molar mass for a given chemical formula.

Since it is very tedious to calculate the molar mass by hand - looking it up
individually in the periodic table - I set out to make a commandline tool to
do it for me. THIS IS NOT GUARANTEED TO WORK. This is just a pet project 
I made for fun.

As it is now there is a working console version, which can be compiled on:
- Linux using gcc
- Windows using gcc from mingw
- OS X using clang

Of course no strict testing has been conducted - especially on Windows and
OS X, since Linux is the primary target - however it did compile and run.

Manual
------------------------------------------------------------------------------
This will explain how the console version of the program is run, as well as
how to use the flags.  The program is invoked as following:

	chemtool [FORMULA] [-s] [-q]

#### Arguments:

	FORMULA
	
The chemical formula to parse. It can only contain letters,
number and parentheses. All elements must begin with a capital
letter (Na, He, U, etc.). The formula cannot begin with 
a number. Note that you can supply more than one element by
seperating them with a space. If no elements are given
the program will ask for one.

Some examples:

	H2O
	CH3CH2CH2CH2CH2CH3
	CH3(CH2)4CH3       <-- same as above
	NaCl H2O CH4       <-- more than one element

#### Flags:

	-s
	
Sparse output. Only print the resulting molar mass
for each element.

	-q
	
Disable any promts. Only has any effect if the program has to
ask for a formula. Use this to make piping more smooth,
as the program will not wait after printing the output, and 
will not print a message asking for a formula.

How to build
------------------------------------------------------------------------------
To build the command line version, navigate to the parent directory and call

	make cli

To build the gui version you are probably better off just doing it yourself.
