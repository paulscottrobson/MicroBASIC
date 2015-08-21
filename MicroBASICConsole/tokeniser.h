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

int TOKTokeniseLine(unsigned char *sourceCode,unsigned char *objectCode,int objectLength);
void TOKTokeniserTest(void);

#endif // TOKENISER_H_INCLUDED
