#ifndef _esparsa_h_
#define esparsa_h_

#define SUCESSO 0
#define ERRO_MATRIZ -1
#define ERRO_POS -2


struct esparsaElem{
    int col,lin;                    // linha e coluna 
    int elem;                       // guarda elemento
    struct esparsaElem *colProx,*linProx; // ponteiro para o proxino elemento
};

struct esparsaMatriz{
    int constante; // contante da matriz 
    int ncol,nlin; // quantidade maxima de linhas e colunas 
    struct esparsaElem **col,**lin; /// guarda os pronteiros para linhas e colunas
};

typedef struct esparsaElem ESPARSA_ELEM;
typedef struct esparsaMatriz ESPARSA_MATRIZ;

// operação basicas
ESPARSA_MATRIZ *criarMatriz(int,int,int); // criar matriz
int addMatriz(ESPARSA_MATRIZ*,int,int,int);// elementos
int getMatriz(ESPARSA_MATRIZ*,int,int); // dar get em um elemento da matriz
int freeMatriz(ESPARSA_MATRIZ*); // dar free na matriz

ESPARSA_MATRIZ* somaMatriz(ESPARSA_MATRIZ*,ESPARSA_MATRIZ*);
ESPARSA_MATRIZ* multMatriz(ESPARSA_MATRIZ*,ESPARSA_MATRIZ*);

void imprimir_matriz(ESPARSA_MATRIZ *);
#endif