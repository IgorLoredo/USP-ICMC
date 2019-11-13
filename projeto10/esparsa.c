#include <stdio.h>
#include <stdlib.h>

#include "esparsa.h"


ESPARSA_MATRIZ *criarMatriz(int lin ,int col ,int cont){
    ESPARSA_MATRIZ *new = (ESPARSA_MATRIZ*)malloc(sizeof(ESPARSA_MATRIZ));
    new->constante = cont;
    new->nlin = lin;
    new->ncol = col;
    new->lin = (ESPARSA_ELEM**)calloc(lin,sizeof(ESPARSA_ELEM*));    
    new->col = (ESPARSA_ELEM**)calloc(col,sizeof(ESPARSA_ELEM*));
    return new;
}

int addMatriz(ESPARSA_MATRIZ* matriz,int lin ,int col ,int elem){
    if(!matriz) return ERRO_MATRIZ;
    if(col < 0 || lin < 0 || lin >=matriz->nlin ||col>= matriz->ncol)
        return ERRO_POS;

    ESPARSA_ELEM **px = &matriz->lin[lin];
    ESPARSA_ELEM **py = &matriz->col[col];

    while (*px && ((*px)->lin < lin)) px = &(*px)->linProx;
	while (*py && ((*py)->col < col)) py = &(*py)->colProx;

    if (*px && *py && (*px)->lin == lin && (*py)->col == col) {
		(*px)->elem = elem;
	} else {
		ESPARSA_ELEM *new = 
			(ESPARSA_ELEM *) 
				malloc(sizeof(ESPARSA_ELEM));

		new->col = col;
		new->lin = lin;
		new->elem = elem;
		new->colProx = *px;
		new->linProx = *py;
		*px = *py = new;
	}
    return SUCESSO;
} 

int getMatriz(ESPARSA_MATRIZ* matriz,int lin ,int col){
    if(!matriz) return ERRO_MATRIZ;
    if(col < 0 || lin < 0 || lin >=matriz->nlin ||col>= matriz->ncol)
        return ERRO_POS;

    ESPARSA_ELEM **px = &matriz->lin[lin];
    ESPARSA_ELEM **py = &matriz->col[col];

    while (*px && ((*px)->lin < lin)) px = &(*px)->linProx;
	while (*py && ((*py)->col < col)) py = &(*py)->colProx;

    if (*px && *py && (*px)->lin == lin && (*py)->col == col) {
		return (*px)->elem;
	}

    return matriz->constante;
}

int freeMatriz(ESPARSA_MATRIZ *matriz) {
	if (!matriz) return ERRO_MATRIZ;

	int i;
	ESPARSA_ELEM *p;

	for (i = 0; i < matriz->nlin; i++) {
		while (p = matriz->lin[i]) {
		    matriz->lin[i] = p->linProx;
			free(p);
		}
	}
	free(matriz->lin);
	free(matriz->col);
	free(matriz);
}