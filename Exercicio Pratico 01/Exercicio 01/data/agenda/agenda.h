/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Including some library
#ifndef _partida_h
#define _partida_h

// Define struct



typedef struct AGENDA *pAGENDA;
typedef struct AGENDA **ppAGENDA;

typedef struct AGENDA{
	int 	cod;
	char	nome[30];
	char	end[30];
	char	fone[20];
}AGENDA;

#endif
