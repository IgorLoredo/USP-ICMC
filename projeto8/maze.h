#ifndef maze_h
#define maze_h


struct grafo{
    int ponto;
    int aberto;
    int visitado;
    int camara;
    struct grafo **prox;
};

struct pilha{
    struct grato **pilha;
    int tam;
};

typedef struct grafo GRAFO;
typedef struct pilha pilha_grafo;

// pilha e operações
pilha_grafo *new_pilha();

GRAFO *iniciarGrafo(int,int); // vet,aberto

#endif