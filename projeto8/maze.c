#include <stdlib.h>
#include <stdio.h>
#include <maze.h>


GRAFO *iniciarGrafo(int ponto,int aberto){
    GRAFO *new = (GRAFO*)calloc(1,sizeof(GRAFO));
    new->aberto = aberto;
    new->ponto = ponto;
    return new;
}

pilha_grafo *new_pilha(){
    pilha_grafo *new = (pilha_grafo*)calloc(1,sizeof(pilha_grafo));
    return new;
}