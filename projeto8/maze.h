#ifndef maze_h
#define maze_h

#define SUCESS 0
#define ERRO_LAB -1
#define ERRO_PILHA -2

struct grafo{
    float x,y;
    char aberto;
    int vistado;
    int pos;
    int liga;
    struct grafo **no;
}; // elememnto

struct lab{
    int Npontos,Ncamaras,Nsegmentos;
    struct grafo **vet;
}; // struct para guardar o labirinto

struct pilha {
	int cap;
	int *vet;
}; // pilha

typedef struct pilha PILHA;
typedef struct grafo GRAFO;
typedef struct lab LAB;

PILHA *criarpilha();
int imprimePilha(PILHA*);
int empilhar(PILHA*,int);
int reempilhar(PILHA*);
LAB *iniciar_lab(int);
GRAFO *iniciarGrafo(float,float,int);
int insereCamara(LAB*,int,int);
int insereSeg(LAB*,int,int);
int processar(LAB*,int);
int distancia(LAB*,int,int);
int esvaziaPilha(PILHA*);
int freeLab(LAB*);
#endif