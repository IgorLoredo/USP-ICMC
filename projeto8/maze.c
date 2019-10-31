#include <stdlib.h>
#include <stdio.h>
#include <maze.h>


GRAFO *iniciarGrafo(float x,float y){
    GRAFO *new = (GRAFO*)calloc(1,sizeof(GRAFO));
    new->y = y;
    new->x = x;
    return new;
}

/*
pilha_grafo *new_pilha(){
    pilha_grafo *new = (pilha_grafo*)calloc(1,sizeof(pilha_grafo));
    return new;
} */
  
LAB *iniciar_lab(int n){
    LAB *new = (LAB*)calloc(1,sizeof(LAB));
    new->vet = (GRAFO**)malloc(sizeof(GRAFO*)*n);
    return new;
}