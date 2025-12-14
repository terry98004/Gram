// -------------------------------------------------------------------
// Program last modified December 7, 2025. 
// Copyright (c) 2025 Terrence P. Murphy
// MIT License -- see gram.c for details.
// -------------------------------------------------------------------

#include <quadmath.h>
#define MPFR_WANT_FLOAT128 1
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <mpfr.h>

#include "hgt.h"
#include "gram.h"


extern struct	HGT_INIT	hgt_init;

// -------------------------------------------------------------------
// We compute the Gram points here.  The loop is over the count of
// different 'n' values to compute (based on gram.CountN). 
// Inside the loop, we call ComputeGram and then print the result.
// -------------------------------------------------------------------
int ComputeGramPoints(struct GRAM gram)
{
mpfr_t			Result, N, Accuracy;
int				i;

// -------------------------------------------------------------------
// Initialize our MPFR variables.  The 'n' value is obtained
// from the gram.nBuf string, and the count of consecutive Gram points
// to compute / display is from gram.CountN.
//
// AS OF NOW, WE HAVE NOT DONE ANY CHECKING TO LIMIT THE SIZE OF N.
//
// We use the mpfr_set_str function because the MPFR FAQ says that the
// other variations such as mpfr_set_ld are much less accurate.
// -------------------------------------------------------------------
mpfr_inits2 (hgt_init.DefaultBits, Result, N, Accuracy, (mpfr_ptr) 0);
mpfr_set_str (N, gram.nBuf, 10, MPFR_RNDN);
mpfr_set_str (Accuracy, "0.1", 10, MPFR_RNDN);
mpfr_pow_ui(Accuracy, Accuracy, gram.AccuracyZeros, MPFR_RNDN);
mpfr_div_ui(Accuracy, Accuracy, 2, MPFR_RNDN);

//mpfr_printf("N = %.14Rf, Accuracy = %.14Rf \n", N, Accuracy);

for(i = 0; i < gram.CountN; i++) {
	GramAtN(&Result, N, Accuracy);
	mpfr_printf("N = %.0Rf, Gram point = %.*Rf \n", N, gram.ReportDecimals, Result);
	mpfr_add_ui(N, N, 1, MPFR_RNDN);
	}

// -------------------------------------------------------------------
// We are done with the MPFR system.  Clear our local MPFR variables.
// -------------------------------------------------------------------
mpfr_clears (Result, N, Accuracy, (mpfr_ptr) 0);
return(1);
}


// -------------------------------------------------------------------
// For the given 'T', we compute the largest Gram point <= T.
// We obtain 'T' from gram.tBuf and convert it to an MPFR variable.
// -------------------------------------------------------------------
int ComputeGramNearT(struct GRAM gram)
{
mpfr_t			Result, T;

// -------------------------------------------------------------------
// Initialize our local MPFR variables.  
// -------------------------------------------------------------------
mpfr_inits2 (hgt_init.DefaultBits, Result, T, (mpfr_ptr) 0);

mpfr_set_str (T, gram.tBuf, 10, MPFR_RNDN);
GramNearT(&Result, T);
mpfr_printf("For T = %.*Rf, we have N = %.2Rf \n", gram.tDecimalDigits, T, Result);

// -------------------------------------------------------------------
// We are done with the MPFR system.  Clear our local MPFR variables.
// -------------------------------------------------------------------
mpfr_clears (Result, T, (mpfr_ptr) 0);
return(1);
}


