// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		main.c
//		Purpose:	Tokeniser test file.
//		Created:	12th September 2015
//		Author:		Paul Robson (paul@robsons->org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"

static BYTE8 _temp[1024];

int main(int argc,char **argv) {
	for (int i = 1;i < argc;i++) {
		printf("String: {%s}\n",argv[i]);
		BYTE8 *result = TOK_TokeniseString((BYTE8 *)argv[i]);
		printf("Tokens: ");
		strcpy((char *)_temp,(char *)result);
		while (*result != '\0') {
			if (*result <= 0x20 || *result >= 0x7F) 
				printf("[%02x] ",*result);
			else
				printf("[%c] ",*result);
			result++;
		}
		printf("\n");
		printf("DeToken: {%s}\n",TOK_DeTokeniseString(_temp));

	}
	return 0;
}