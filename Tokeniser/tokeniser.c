// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		tokeniser.c
//		Purpose:	Tokeniser 
//		Created:	12th September 2015
//		Author:		Paul Robson (paul@robsons->org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <string.h>
#include <ctype.h>
#include "tokeniser.h"

static BYTE8 _TOK_Buffer[TOKENISER_BUFFER_SIZE+8];									// Tokenised stuff goes here.

#define INCLUDE_STATIC_KEYWORD_LIST 												// We need the text stuff.

#include "keywords.h"																// Auto generated tokens and IDs

// *******************************************************************************************************************************
//						Compare two strings to see if they are the same over a specified length
// *******************************************************************************************************************************

static BYTE8 _TOK_Compare(char *s1,BYTE8 *s2,BYTE8 length) {
	while (toupper(*s1) == toupper(*s2) && length > 0 && *s1 != '\0') {
		s1++;s2++;length--;
	}
	return (length != 0);
}

// *******************************************************************************************************************************
//										Tokenise string into Micro BASIC format
// *******************************************************************************************************************************

BYTE8 *TOK_TokeniseString(BYTE8 *input) {
	BYTE8 *p = _TOK_Buffer;
	BYTE8 isComment = 0;
	BYTE8 isQuote = 0;
	while (*input != '\0') {														// Process string.
		ASSERT(p != _TOK_Buffer+TOKENISER_BUFFER_SIZE);								// Not out of space.
		BYTE8 best = 0xFF;															// Best found so far.
		BYTE8 bestLength = 0;														// Its length.
		for (BYTE8 n = KEYWORD_BASE;n < KEYWORD_END;n++ ) {							// Check each token.
			char *keyword = _keywords[n - KEYWORD_BASE];							// Get a pointer to it.
			if (_TOK_Compare(keyword,input,strlen(keyword)) == 0) {					// Matches ?
				if (strlen(keyword) > bestLength) {									// And is better, e.g. a longer match.
					best = n;bestLength = strlen(keyword);							// Record keyword and length
				}
			}
		}
		if (*input == '"' || *input == '\'') isQuote = (isQuote == 0);			// Quotes
		if (best == KWD_COMMENT) isComment = 1;										// Found a comment
		if (best != 0xFF && isComment == 0 && isQuote == 0) {						// Have we found a token ?
			*p++ = best;															// Store that token in the buffer
			input = input + bestLength;												// Skip over it in the input
		} else {																	// Not a token.
			if (!isspace(*input) || isComment != 0 || isQuote != 0) {				// If not space, copy it in in L/C, maybe.
				*p = *input;
				if (isComment == 0 && isQuote == 0) *p = tolower(*p);				// Capitalise if not comment, string.
				p++;
			} 
			input++;																// Next character
		}
	}
	*p = '\0';																		// Add trailing End of string.
	return _TOK_Buffer;																// Return the buffer.
}

// *******************************************************************************************************************************
//											Detokenise string into readable(ish) ASCII
// *******************************************************************************************************************************

BYTE8 *TOK_DeTokeniseString(BYTE8 *input) {
	BYTE8 *p = _TOK_Buffer;															// Buffer pointer.
	while (*input != '\0') {														// Process string.
		ASSERT(p <= _TOK_Buffer+TOKENISER_BUFFER_SIZE);								// Not out of space.
		if (*input < 0x80) {														// Is it a ASCII character ?
			*p++ = *input++;														// If so, just copy it.
		} else {																	// No, it's a token.
			char *token = _keywords[*input++-KEYWORD_BASE];							// Get keyword
			while (*token != '\0') *p++ = *token++;									// Copy the token in.
			if (isalpha(*--token)) *p++ = ' ';
		}
	}
	*p++ = '\0';																	// Add trailing NULL
	return _TOK_Buffer;
}