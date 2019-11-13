#include <stdio.h>
#include <stdlib.h>
#include <esparsa.h>

// operação baisicas para rodar uma matriz esparsa
ESPARSA_MATRIZ *criarMatriz(int lin ,int col ,int cont){
    ESPARSA_MATRIZ *new = (ESPARSA_MATRIZ*)malloc(sizeof(ESPARSA_MATRIZ));
    new->constante = cont;
    new->nlin = lin;
    new->ncol = col;
    new->lin = (ESPARSA_ELEM**)calloc(lin,sizeof(ESPARSA_ELEM*));    
    new->col = (ESPARSA_ELEM**)calloc(col,sizeof(ESPARSA_ELEM*));
    return new;
} // cria matriz esparsa com as colunas e linhas e a constante

int addMatriz(ESPARSA_MATRIZ* matriz,int lin ,int col ,int elem){
    if(!matriz) return ERRO_MATRIZ;
    if(col < 0 || lin < 0 || lin >=matriz->nlin ||col>= matriz->ncol)
        return ERRO_POS;

    ESPARSA_ELEM **px = &matriz->lin[lin];
    ESPARSA_ELEM **py = &matriz->col[col]; // pega o primeiro elemento da matriz na linha e coluna

    while (*px && ((*px)->col < col)) px = &(*px)->colProx;
	while (*py && ((*py)->lin < lin)) py = &(*py)->linProx; // precorre linha e coluna até chegar no elemento ou posição

    if (*px && *py && (*px)->lin == lin && (*py)->col == col) {
		(*px)->elem = elem; // quando chega tudo no lugar certo
	} else {
         // caso n exista a posição
		ESPARSA_ELEM *new = (ESPARSA_ELEM *)malloc(sizeof(ESPARSA_ELEM));

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

    while (*px && ((*px)->col < col)) px = &(*px)->colProx;
	while (*py && ((*py)->lin < lin)) py = &(*py)->linProx; // precorre linha e coluna até chegar no elemento ou posição

    if (*px && *py && (*px)->lin == lin && (*py)->col == col) {
		return (*px)->elem; // caso exista o elemento
	}

    return matriz->constante;
} // dar get no elemento caso exista, se n retona a constante

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
    return SUCESSO;
}/// dar free 

void imprimir_matriz(ESPARSA_MATRIZ *matriz) {
    int i;
    ESPARSA_ELEM *paux;
    printf("-1 %d %d\n", matriz->nlin, matriz->ncol);

    for (i = 0; i < matriz->nlin; i++) {
        
        for (paux = matriz->lin[i]; paux != NULL; paux = paux->linProx) {
            printf("%d %d %d\n", paux->lin, paux->col, paux->elem);
        }
    } 
    /*for (i = 0; i < matriz->nlin; i++) {
        paux = matriz->lin[i];
        while(paux ) {
            printf("%d %d %d\n", paux->lin, paux->col, paux->elem);
            paux = paux->colProx;
        }
    } */
}

ESPARSA_MATRIZ* somaMatriz(ESPARSA_MATRIZ*A,ESPARSA_MATRIZ*B){
    if(!A || !B) return NULL;
    ESPARSA_MATRIZ*new = criarMatriz(A->nlin,A->ncol,0);
    int i,j,soma,a ,b;
    for(i=0;i<A->nlin;i++){
        for(j=0;j<A->ncol;j++){
            a = getMatriz(A,i,j);
            b =getMatriz(B,i,j);
            soma  = a + b;
            addMatriz(new,i,j,soma);
        }
    }
    return new;
}