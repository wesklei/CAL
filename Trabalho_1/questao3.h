/* 
 * File:   questao3.h
 * Author: Wesklei Migliorini <wesklei at wbezerra.com.br>
 *
 * Created on May 4, 2014, 8:03 PM
 */

#ifndef QUESTAO3_H
#define	QUESTAO3_H

#include "main.h"

typedef struct NoABB *pNoABB, **ppNoABB;

typedef struct NoABB {
    void *dado;
    pNoABB pai, esq, dir;
} NoABB, *pNoABB, **ppNoABB;

typedef struct ABB {
    int tinfo;
    pNoABB raiz;
} ABB, *pABB, **ppABB;

#define MAXSTACKSIZE 100
typedef struct STACK {           /* Structure definition for stack */
	NoABB s[MAXSTACKSIZE];
	int topo;
} STACK, *pSTACK, **ppSTACK;

#endif	/* QUESTAO3_H */

