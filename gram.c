// -------------------------------------------------------------------
// Program last modified December 7, 2025. 
// -------------------------------------------------------------------

/*
MIT License

Copyright (c) 2025 Terrence P. Murphy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <quadmath.h>
#define MPFR_WANT_FLOAT128 1

#include <time.h>
#include <stdio.h>
#include <math.h>			
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>			// for command line argument processing
#include <mpfr.h>

#include "hgt.h"
#include "gram.h"


const char sUsage[] = "Command Line Parameters\n" \
 "-n [integer]	The Gram point n value >= -1. This or -t is required. (Digits and '+-' only).\n" \
 "-t [positive number]	Find largest Gram points <= 't', with 't' >= 100. This or -n is required. \n" \
 "-a [positive integer]	Gram point accurate to this many decimal zeros - defaults to 10.\n" \
 "-c [positive integer]	Count of the number of n values to report - defaults to 1. for -n switch only.\n" \
 "-p [positive integer]	Gram point decimal points to show in report - defaults to 6.\n" \
 "-b [positive integer]	Floating point bits: 128 <= b <= 1024 - defaults to 256.\n" \
 "-k [positive integer]	Allowed number of threads to use - defaults to 1, maximum of 8.\n" \
 "-d [positive integer]	Used for debugging only.  Please disregard.\n" \
 "-h			Show command line parameters.  All other parameters will be ignored.\n" \
 "-s			Report the total seconds taken to compute the Gram Point values.\n"\
 "-v			Verbose report (otherwise CSV only)."; 

const char sCopyright[] = "Copyright 2025 by Terrence P. Murphy." \
" Licensed under MIT License.\n\n"; 


int main( int argc, char *argv[] )  
{
int				c;
struct	GRAM	gram;

gram.nResult 		= 0;
gram.tResult		= 0;
gram.CountN			= 1;
gram.bVerbose 		= false;
gram.bSeconds		= false;
gram.DebugFlags		= 2311; // (2 * 3 * 5 * 7 * 11) + 1
gram.ReportDecimals	= 6;
gram.AccuracyZeros	= 10;
gram.DefaultBits	= HGT_PRECISION_DEFAULT;
gram.Threads 		= 1;

fprintf(stderr, "%s", sCopyright);
if(argc == 1) {
	printf("%s\n", sUsage);
	exit(EXIT_FAILURE);
	}
opterr = 0; // To prevent _getopt from printing an error message on standard error

while ((c = getopt (argc, argv, "n:t:c:p:k:a:b:d:hvs")) != -1) {
	switch (c)
		{
		case 'h':
			printf("%s\n", sUsage);
			exit(EXIT_SUCCESS);
		case 'v':
			gram.bVerbose = true;
			break;
		case 's':
			gram.bSeconds = true;
			break;			
		case 'n':
			gram.nResult = ValidateGramN(optarg);	
			if(gram.nResult < 1){
				printf("Invalid argument to -n \n");
				return(EXIT_FAILURE);
				}
			strcpy(gram.nBuf, optarg);
			break;
		case 't':
			gram.tResult = ValidateGramT(optarg);	
			if ( gram.tResult < 1) {
				printf("Invalid argument to -t \n");
				return(EXIT_FAILURE);
				}
			strcpy(gram.tBuf, optarg);
			gram.tDecimalDigits =  GetDecimalDigits(gram.tBuf);
			break;			
		case 'c':		
			gram.CountN = ValidateCount(optarg);	
			if(gram.CountN < 1) {
				printf("Invalid argument to -g \n");
				return(EXIT_FAILURE);
				}
			break;					
		case 'p':
			gram.ReportDecimals = ValidateReportDecimalPlaces(optarg);	
			if(gram.ReportDecimals < 1) {
				printf("Invalid argument to -g \n");
				return(EXIT_FAILURE);
				}
			break;
		case 'k':
			gram.Threads = ValidateThreads(optarg);
			if(gram.Threads < 1) {
				printf("Invalid argument to -k \n");
				return(EXIT_FAILURE);
				}
			break;				
		case 'a':
			gram.AccuracyZeros = ValidateGramAccuracy(optarg);
			if(gram.AccuracyZeros < 1) {
				printf("Invalid argument to -a \n");
				return(EXIT_FAILURE);
				}
			break;							
		case 'd':
			gram.DebugFlags = ValidateDebugFlags(optarg);	
			if(gram.DebugFlags < 1) {
				printf("Invalid argument to -d \n");
				return(EXIT_FAILURE);
				}
			break;			
		case 'b':
			gram.DefaultBits = ValidatePrecisionMPFR(optarg);	
			if(gram.DefaultBits < 1) {
				printf("Invalid argument to -b \n");
				return(EXIT_FAILURE);
				}
			break;
		case '?':
		case ':':
		default:
			printf("Option -%c is either unknown or missing its argument\n", optopt);
			return (EXIT_FAILURE);
		}
	}
if(gram.nResult == 1 && gram.tResult == 1){
	printf("Only one of the -n and -x parameters is allowed.\n");
	return(EXIT_FAILURE);
	}

if(gram.nResult == 0 && gram.tResult == 0){
	printf("Exactly one of the -n and -x parameters is required.\n");
	return(EXIT_FAILURE);
	}

// -------------------------------------------------------------------
// We have finished validating the command line parameters.  Now compute 
// and printf our HardyZ results.  Time the seconds it takes to do the
// computations if the user enters the -s command line parameter.
// -------------------------------------------------------------------
clock_t	t;
double 	time_taken;

t = clock(); 
InitMPFR(gram.DefaultBits, gram.Threads, gram.DebugFlags, false);
if(gram.nResult == 1)
	{
	ComputeGramPoints(gram); 
	}
else
	{
	ComputeGramNearT(gram);
	}
CloseMPFR();
t = clock() - t; 
time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
if(gram.bSeconds){
	printf("Compute took %f seconds to execute \n", time_taken); 
	}
return(EXIT_SUCCESS);
}


//printf("Size of unsigned int: %zu bytes\n", sizeof(unsigned int));						4 bytes
//printf("Size of unsigned long int: %zu bytes\n", sizeof(unsigned long int));				4 bytes
//printf("Size of unsigned long long int: %zu bytes\n", sizeof(unsigned long long int));	8 bytes
//quadmath_snprintf (chBuf, sizeof chBuf, "%Qf", N128);

