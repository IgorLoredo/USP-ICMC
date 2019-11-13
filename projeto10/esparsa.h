#ifndef _esparsa_h_
#define esparsa_h_

#define SUCESSO 0
#define ERRO_MATRIZ -1
#define ERRO_POS -2


struct esparsaElem{
    int col,lin;
    int elem;
    struct esparsaElem *colProx,*linProx;
};


struct esparsaMatriz{
    int constante;
    int ncol,nlin;
    struct esparsaElem **col,**lin;
};

typedef struct esparsaElem ESPARSA_ELEM;
typedef struct esparsaMatriz ESPARSA_MATRIZ;


ESPARSA_MATRIZ *criarMatriz(int,int,int);
int addMatriz(ESPARSA_MATRIZ*,int,int,int);
int remover(ESPARSA_MATRIZ*,int,int);

int getMatriz(ESPARSA_MATRIZ*,int,int);
int freeMatriz(ESPARSA_MATRIZ*);
#endif