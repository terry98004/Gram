# Gram
Using the libHGT static library, locates Gram Points

## Overview

We provide here a C program to either: (1) locate Gram Points given a positive integer N, or (2) calculate the associated N for the largest Gram Point less than or equal to a given ordinate 't'. The actual calculation work is done by calls to functions in the **libHGT** static library.  The code here is a front end to that calculating code that: (1) gathers the user-requested parameters for the calculations via the command line, (2) validates those command line parameters (by calls to the library), (3) passes those parameters to the calculating code in the library, and (4) prints (via stdout) a report of those calculations.

To create an executable, you will need two files from the **libHGT** library: (1) the **hgt.h** include file, and (2) the **libhgt.a** static library file.

Like the **libHGT** library, the source code is intended for use with the **gcc** compiler.  Although only tested on 
64-bit Windows 11, the source code should be portable to other 64-bit operating systems supported by **gcc**.

## Building the Executable

For Windows 11 users, an executable is included with any release posted on GitHub.

For other operating systems, you will need to build the executable, as follows.

*  You need the [**gcc**][gcc-gnu-link] C compiler installed on your system.  That installation must include the **libmpfr.a** and **libgmp.a** (floating point) static libraries.

*  From [**libHGT**][libhgt-link], you need to: (1) create the **libhgt.a** static library file, and (2) make that library file plus **hgt.h** visible to the **gcc** compiler.

*  Following the build logic in the **makegram.bat** file, you need to create the necessary 'makefile', in the form that applies to your operating system and the **gcc** compiler.

You can then build the Gram executable from the provided source files.

## Files

This distribution consists of the following files:

  * [README.md][readme-link]. The file you are currently reading.
  
  * [gram.c][gram-c-link]. The entry pont for our program.  This source code file is 
  quite straightforward. We validate the user’s command line input, save their
  choices and then call the 'ComputeAllHardyZ' function, which in turn calls the **libHGT** functions that do the actual calculations.
 
  * [CompGram.c][CompGram-c-link]. This source code file includes the 'ComputeGramPoints' and 'ComputeGramNearT'  functions, which: (1) call the **libHGT** functions that do the actual calculations, and (2) print the output reports.
  
  * [gram.h][gram-h-link]. The is the only (local) include file for the program.  
  
  * [makegram.bat][makegram-bat-link]. The is the "makefile" for the program.  Currently,
  this file is a Windows batch file (**not** an actual makefile), but can be easily converted to 
  a standard makefile.

## Command Line Parameters

 *  -n [integer]	The Gram point n value >= -1. This or -t is required. (Digits and '+-' only).
 *  -t [positive number]	Find largest Gram points <= 't', with 't' >= 100. This or -n is required.
 *  -a [positive integer]	Gram point accurate to this many decimal zeros - defaults to 10.
 *  -c [positive integer]	Count of the number of n values to report - defaults to 1. for -n switch only.
 *  -p [positive integer]	Gram point decimal points to show in report - defaults to 6.
 *  -b [positive integer]	Floating point bits: 128 <= b <= 1024 - defaults to 256.
 *  -k [positive integer]	Allowed number of threads to use - defaults to 1, maximum of 8.
 *  -d [positive integer]	Used for debugging only.  Please disregard.
 *  -h			Show command line parameters.  All other parameters will be ignored.
 *  -s			Report the total seconds taken to compute the Gram Point values.
 *  -v			Verbose report (otherwise CSV only).

**NOTE**: Currently, threads are not actually used (or needed) in Gram Point calculations.

## Terms of use

This **Gram Point Calculator** is free and distributed under the
[**MIT License**][license-link] (MIT). 

We used the [**gcc**][gcc-gnu-link] compiler and the [**MPFR**][mpfr-link] floating point library.
We also used the [**msys2**][msys2-link] software distribution and building platform for windows.
See their respective links for theirs terms of license.  

[website-link]:			https://riemann1859.com
[readme-link]:			https://github.com/terry98004/Gram/blob/master/README.md
[gram-c-link]:			https://github.com/terry98004/Gram/blob/master/gram.c
[CompGram-c-link]:		https://github.com/terry98004/Gram/blob/master/CompGram.c
[gram-h-link]:			https://github.com/terry98004/Gram/blob/master/gram.h
[makegram-bat-link]:	https://github.com/terry98004/Gram/blob/master/makegram.bat
[mpfr-link]:			https://www.mpfr.org/
[gcc-gnu-link]:			https://gcc.gnu.org/
[msys2-link]:			https://www.msys2.org/
[libhgt-link]:			https://github.com/terry98004/libHGT/
