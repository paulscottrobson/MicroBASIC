// *********************************************************************************
// *********************************************************************************
//
//      Name:       tokeniser.c
//      Author:     Paul Robson
//      Purpose:    tokenises MicroBasic text line.
//      Created:    21st Augyst 2015
//
// *********************************************************************************
// *********************************************************************************

#ifndef TOKENISER_H_INCLUDED
#define TOKENISER_H_INCLUDED

int TOKTokeniseLine(char *sourceCode,char *objectCode,int objectLength);
char *TOKExpand(char *tokenisedCode);
void TOKTokeniserTest(void);

#define MAXLINESIZE (128)

#endif // TOKENISER_H_INCLUDED
