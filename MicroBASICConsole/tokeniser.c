// *********************************************************************************
// *********************************************************************************
//
//	  Name:	   tokeniser.c
//	  Author:	 Paul Robson
//	  Purpose:	tokenises MicroBasic text line.
//	  Created:	21st Augyst 2015
//
// *********************************************************************************
// *********************************************************************************

#define INCLUDE_STATIC_KEYWORD_LIST							 					// Bring in the text keywords.

#include "tokeniser.h"
#include "keywords.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int TOKTokeniseLine(char *sourceCode,char *objectCode,int objectLength)
{
	char *pTarget = objectCode;			 					   					// Where the object code goes.
	int  isInQuotes = 0;														// Non zero when in quotes.

	while (*sourceCode != '\0')							 						// Keep going till end of source string.
	{
		if ((pTarget-objectCode) >= objectLength) return -1;					// Doesn't fit.
		if (*sourceCode == '"')
		{
			isInQuotes = (isInQuotes == 0);						 				// Track in Quotes.
		}
		if (isInQuotes || *sourceCode == '"')					   				// Do not capitalise text in quotes.
		{
			*pTarget++ = *sourceCode++;
		}
		else																	// Not in quotes
		{
			if (!isspace(*sourceCode))						  					// Ignore white space.
			{
				int keyFound = -1;
				int keyWord = KEYWORD_BASE;
				while(_keywords[keyWord-KEYWORD_BASE][0] != '\0')			   	// Look through keywords.
				{
					char *current = _keywords[keyWord-KEYWORD_BASE];	   		// Get the current keyword.
					if (strnicmp(current,sourceCode,strlen(current)) == 0)	   	// Keyword match.
					{
						if (keyFound < 0) keyFound = keyWord;			   		// If first update it.
						if (strlen(current) > strlen(_keywords[keyFound-KEYWORD_BASE])) // If it is longer than the current best match
							keyFound = keyWord;									// Override it.
					}
					keyWord++;
				}
				printf("%s %d\n",sourceCode,keyFound);
				if (keyFound < 0)							   					// Not found, copy capitalised
				{
					char c = *sourceCode++;
					*pTarget++ = toupper(c);
				}
				else															// Found a match
				{
					*pTarget++ = (char)(keyFound & 0xFF);				   		// Copy the token
					sourceCode = sourceCode + strlen(_keywords[keyFound-KEYWORD_BASE]); // Skip the keyword
				}
			}
			else
			{
				sourceCode++;							   						// Skip white space
			}
		}
	}
	*pTarget = '\0';															// Add trailing EOS.
	return 0;									   								// and return.
}

static char tokExpanded[MAXLINESIZE+1];											// Output buffer, detokenised line.

char *TOKExpand(char *tokenisedCode)
{
	char *p = tokExpanded;
	while (*tokenisedCode != '\0')
	{
		if (*tokenisedCode & 0x80)
		{
			char *keyWord;
			keyWord = _keywords[*(unsigned char *)tokenisedCode-KEYWORD_BASE];
			if (isalpha(*keyWord)) *p++ = ' ';
			strcpy(p,keyWord);
			p = p + strlen(p);
			if (isalpha(keyWord[strlen(keyWord)-1])) *p++ = ' ';
			tokenisedCode++;
		}
		else
		{
			*p++ = *tokenisedCode++;
		}
	}
	*p = '\0';
	while(isspace(*tokExpanded)) strcpy(tokExpanded,tokExpanded+1);
	while(strstr(tokExpanded,"  ") != NULL)
	{
		char *s = strstr(tokExpanded,"  ");
		strcpy(s,s+1);
	}
	return(tokExpanded);
}

/** \brief Test the Tokeniser
 *
 */

void TOKTokeniserTest(void)
{
	int i;
	char szBuffer[128];
	TOKTokeniseLine("GOSUBX \"Hello \" =len(42)+7 > >=",szBuffer,sizeof(szBuffer));
	for (i = 0;i < strlen(szBuffer);i++)
	{
		int c = szBuffer[i];
		c = c & 0xFF;
		printf("%3d %c %s\n",(int)(c) & 0xFF,(c < KEYWORD_BASE) ? c : '.',(c >= KEYWORD_BASE) ? _keywords[c-KEYWORD_BASE]:"--");
	}
	printf("[%s]\n",TOKExpand(szBuffer));
}
