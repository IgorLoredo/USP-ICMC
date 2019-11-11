#include <stdlib.h>
#include <stdio.h>
#include <maze.h>
#include <math.h>
//#include "maze.h"

/*
    tentei utilizar a estrutura de grafo mesclando alguma forma 
    mais facil de se aplicar e tento fazer uma pilha para guarda o 
    caminho feito, 
*/

GRAFO *iniciarGrafo(float x,float y,int pos){
    GRAFO *new = (GRAFO*)malloc(sizeof(GRAFO));
    new->y = y;
    new->x = x;
    new->pos = pos;
    return new; // inicia estrutura do "grafo"
}

LAB *iniciar_lab(int n){
    LAB *new = (LAB*)calloc(1,sizeof(LAB));
    new->vet = (GRAFO**)malloc(sizeof(GRAFO*)*n);
    return new;
} // estrutura que contem todos os pontos e o grafico

int insereCamara(LAB*p,int camara,int aberto){
    if(!p) return ERRO_LAB; 
    p->vet[camara]->aberto = aberto;
    return SUCESS;
} // para iniciar a camara no ponto

int insereSeg(LAB *lab, int c1, int c2){
    if(!lab) return ERRO_LAB;
  	GRAFO *p = lab->vet[c1];
    p->no = (GRAFO**)realloc(p->no,(sizeof(GRAFO*)*p->liga+1));
    p->no[p->liga] = lab->vet[c2];
    p->liga++;
    return SUCESS;
} // insere o segmentos no grafico

PILHA *criarpilha(){
	PILHA *novo= (PILHA*)calloc(1, sizeof(PILHA));
    novo->cap = -1;
	return novo;
} // cria uma pilha

int empilhar(PILHA* pilha,int x){
	if(!pilha) return ERRO_PILHA;
	pilha->cap++;
	pilha->vet = (int*)realloc(pilha->vet,sizeof(int)*pilha->cap+1);
    pilha->vet[pilha->cap] = x;
	return SUCESS;
} // coloca elementos na pilha

int reempilhar(PILHA* pilha){
	if(!pilha) return ERRO_PILHA;
	int x = pilha->vet[pilha->cap];
	pilha->cap--;
	pilha->vet = (int*)realloc(pilha->vet,sizeof(int)*pilha->cap+1);
	return x;	
} // retira da pilha

int esvaziaPilha(PILHA* p){
    if(!p) return ERRO_PILHA;
    p->cap = -1;
    p->vet = (int*)realloc(p->vet,sizeof(int));
}// esvazia a pilha

int imprimePilha(PILHA* p){
    if(!p) return ERRO_PILHA;
    int i;
    for(i=0;i<p->cap;i++){
            printf("%d ",p->vet[i]);
    }
    return SUCESS;
} // imprime a pilha


int distancia(LAB* lab,int x1 , int x2){
    if(!lab) return ERRO_LAB;
    int result;
    int d1 = lab->vet[x2]->x - lab->vet[x1]->x;
    int d2 = lab->vet[x2]->y - lab->vet[x1]->y;
    result = pow(d1,2) + pow(d2,2);
    result =  pow(result,1.0/2.0); 
     return result;
} // calcular a distancia dos elementos


// tenta achar os procurando por todo labirinto até n tiver mais possivilidades
int processar(LAB *lab,int inicial){
	if(!lab) return ERRO_LAB;
	PILHA *pi = criarpilha();
	GRAFO **p = &lab->vet[inicial];
	int flag1=1, flag2 = 1; // inicai as flags como 1
    int camara =1;
    int seg = 0,dist;

    while(flag2 && p){
        empilhar(pi,(*p)->pos); // empilha o primeiro elemento
        while(flag1 && p){
            if((*p)->aberto == 1){   
               empilhar(pi,(*p)->pos+1);
                flag1 = 0; // muda a flag para quebrar o while
                camara++;
                seg++;
                (*p)->aberto = 0; // torna a camara fechada
                printf("%d ",pi->cap);
                imprimePilha(pi); // printando a pilha
                esvaziaPilha(pi); // esvazia ela
                dist = distancia(lab,inicial,(*p)->pos-1);
                printf("%d\n",dist);
            }
            else{ 
                if((*p)->liga > 1) // para verficar se tem mais de um caminho na camara
                    (*p)->vistado++;
                empilhar(pi,(*p)->pos+1);
                p = &(*p)->no[(*p)->vistado];

              
                seg++;
                camara++;
            }

          
        }

   if(camara >= lab->Ncamaras+1 || seg >= lab->Nsegmentos+1 || !p)
        flag2 = 0;
    else{
        flag1 = 1; 
        seg =0;
        camara =0;
    }
    
    p = &lab->vet[inicial];
    }
   
    free(pi);
	return SUCESS;
}


int freeLab(LAB *p){
    if(!p) return ERRO_LAB;
    int i;
    for(i=0;i<p->Npontos;i++)
        free(p->vet[i]);
 
    free(p);
    return SUCESS;
}// dar free no labrinto