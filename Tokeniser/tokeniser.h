// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		tokeniser.h
//		Purpose:	Tokeniser (header)
//		Created:	12th September 2015
//		Author:		Paul Robson (paul@robsons->org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _TOKENISER_H
#define _TOKENISER_H
#include "types.h"

#define TOKENISER_BUFFER_SIZE	(128) 												// How long we can go !

BYTE8 *TOK_TokeniseString(BYTE8 *input);											// Tokenise the buffer.
BYTE8 *TOK_DeTokeniseString(BYTE8 *input);											// Detokenise the buffer.

#endif