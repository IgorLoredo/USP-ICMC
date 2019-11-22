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

    if (*px && *py && (*px)->col == col && (*py)->lin == lin) {
		(*px)->elem = elem; // quando chega tudo no lugar certo
	} else {
         // caso n exista a posição
		ESPARSA_ELEM *new  = (ESPARSA_ELEM *)malloc(sizeof(ESPARSA_ELEM));
        // faz atriuições para cada vetor apontar para o novo elemento
		new->col = col;
		new->lin = lin;
		new->elem = elem;
		new->linProx = *px;
		new->colProx = *py;
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

    if (*px && *py && (*px)->col == col && (*py)->lin == lin) {     
		return(*px)->elem; // quando chega tudo no lugar certo
	}

    return matriz->constante;
} // dar get no elemento caso exista, se não retona a constante

int freeMatriz(ESPARSA_MATRIZ *matriz) {
	if (!matriz) return ERRO_MATRIZ;
	int i;
	ESPARSA_ELEM *p;

	for (i = 0; i < matriz->nlin; i++) {
		while (p = matriz->lin[i]) {
		    matriz->lin[i] = p->colProx;
			free(p); // free no elemento
		}
	}
	free(matriz->lin); // free na coluna e linha
	free(matriz->col);
	free(matriz);
    return SUCESSO;
}/// dar free 

void imprimir_matriz(ESPARSA_MATRIZ *matriz) { // codigo pronto
    int i;
    ESPARSA_ELEM *paux;
    printf("-1 %d %d\n", matriz->nlin, matriz->ncol);

    for (i = 0; i < matriz->nlin; i++) { // imprime a matriz
        for (paux = matriz->lin[i]; paux != NULL; paux = paux->colProx) {
            printf("%d %d %d\n", paux->lin, paux->col, paux->elem);
        }
    } 
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
            if(soma)
             addMatriz(new,i,j,soma);
        }
    }

 ////////////// tentei fazer parte do codigo para diminuir o tempo de resposta, mas n conseguir,
 ////////////// deixei esse trecho para avalição (se possivel) para me mostrar meu erro
   /* ESPARSA_ELEM **auxA,**auxB;
     for (i = 0; i < A->nlin; i++) {
         auxA = &A->lin[i];
         auxB = &B->lin[i];
        //printf("linha %d   elemento %d  coluna %d \n",i,(*auxA)->elem,(*auxA)->col);
        if(*auxA && *auxB){
           // printf("linha : %d\n",i);
            while((*auxA) || (*auxB)){
               
             if((*auxA)  && (*auxB)){ // se existir os dois elementos
                    if((*auxA)->col == (*auxB)->col ){ // caso tiver na mesma coluna
                        //printf("aqui\n");
                       j = (*auxA)->col;
                        a = getMatriz(A,i,j);
                        b =getMatriz(B,i,j);
                        soma  = a + b;
                        
                        addMatriz(new,i,j,soma); 
                    }
                    else if((*auxA)->col < (*auxB)->col){ // caso a coluna do a for menor que a do b
                        addMatriz(new,i,(*auxA)->col,(*auxA)->elem);
                         
                    }else if((*auxA)->col > (*auxB)->col){// caso a coluna b for menor que a
                        addMatriz(new,i,(*auxB)->col,(*auxB)->elem); //
                       
                    }
                    auxA = &(*auxA)->colProx;
                    auxB = &(*auxB)->colProx;
                    
                }else if((*auxA) && !(*auxB)){ // caso a exista e b não
                    addMatriz(new,i,(*auxA)->col,(*auxA)->elem);
                     auxA = &(*auxA)->colProx;
                }
                else if(!(*auxA) && (*auxB)){
                    addMatriz(new,i,(*auxB)->col,(*auxB)->elem);   
                    auxB = &(*auxB)->colProx;
                }
               
            }

        } else if(!(*auxA) && (*auxB)){
            while((*auxB)){
                addMatriz(new,i,(*auxB)->col,(*auxB)->elem);
                auxB = &(*auxB)->colProx;
            }
        }else if((*auxA) && !(*auxB)){
               while((*auxA)){
                addMatriz(new,i,(*auxA)->col,(*auxA)->elem);
                auxA = &(*auxA)->colProx;
            } 
        } 
    } */
 
    return new;
}

ESPARSA_MATRIZ* multMatriz(ESPARSA_MATRIZ* A,ESPARSA_MATRIZ*B){ // nmultiplicação de matrizes
    int i,j,somaprod=0,a;

    ESPARSA_MATRIZ* new = criarMatriz(A->nlin,B->ncol,0);
    ESPARSA_ELEM *auxA,*auxB;
    for(j=0;j<B->ncol;j++){
        for(i=0;i<A->nlin;i++){
            auxA = A->lin[i];
            //for(j=0;j<B->lin){
               somaprod =0; 
            while(auxA){
                a = getMatriz(B,auxA->col,j); // pega um elemnto na posição da coluna e linha
                if(a!=0 ) // se elçe for diferente de 0 ele soma 
                    somaprod += auxA->elem *a;

                auxA = auxA->colProx;
            }
            if(somaprod)
            addMatriz(new,i,j,somaprod);

            
        }
    }
       // fiz desses jeito para ficar mais rapido a multiplicação
    return new;
}
