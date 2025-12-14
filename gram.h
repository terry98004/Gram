// -------------------------------------------------------------------
// Program last modified December 7, 2025. 
// Copyright (c) 2025 Terrence P. Murphy
// MIT License -- see gram.c for details.
// -------------------------------------------------------------------

struct GRAM {
	char			nBuf[HGT_MAX_CMDLINE_STRLEN + 2];	// entered -n value in chars
	char			tBuf[HGT_MAX_CMDLINE_STRLEN + 2];	// entered -t value in chars
	int				nResult;							// -n parsing result value (if any)
	int				tResult;							// -x parsing result value (if any)
	int 			CountN;     						// number of n values to check
	bool			bVerbose;							// verbose report? T/F
	bool			bSeconds;							// report computed second taken T/F
	int				DebugFlags;							// used for debugging
	int				ReportDecimals;						// digits after '.' in Gram value
	int				AccuracyZeros;						// zero's digits after '.' in accuracy
	int				DefaultBits;						// Bits for MPFR floating point 
	int				tDecimalDigits;						// DecimalDigits in 'T' string
	int				Threads;
}; 

int ComputeGramPoints(struct GRAM gram);
int ComputeGramNearT(struct GRAM gram);



