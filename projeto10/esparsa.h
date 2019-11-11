#ifdef esparsa_h
#define esparsa_h

#define SUCCESS 0

struct esparsa_elem{
    int col,lin;
    int elem;
    struct esparsa_elem *colProx,*linProx;
};
struct esparsa_matriz{
    int constante;
    int ncol,nlin;
    struct esparsa_elem **col,**lin;
};

typedef struct esparsa_elem ESPARSA_ELEM;
typedef struct esparsa_matriz ESPARSA_MATRIZ;

ESPARSA_MATRIZ *criarMatriz(int,int);
int addMatriz(ESPARSA_MATRIZ*,int,int,int);
int remover(ESPARSA_MATRIZ*,int,int);

int apagarMatriz(ESPARSA_MATRIZ*);
#endif