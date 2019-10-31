#ifndef maze_h
#define maze_h



struct grafo{
    float x,y;
    char a;;
    int vistado;
    struct grafo **no;
};

struct lab{
    int Npontos,Ncamaras,Nsegmentos;
    struct grafo **vet;
};

typedef struct grafo GRAFO;
typedef struct lab LAB;

LAB *iniciar_lab(int);

#endif