#include <stdlib.h>
#include <stdio.h>
#include <maze.h>
//#include "maze.h"

int main(){
    int i,inicial,camara,aberto,c1,c2;
    float x,y;
    int npont,ncamara,nSeg;
    scanf("%d",&npont);
    LAB *labirinto = iniciar_lab(npont+1);

    for(i=0;i<npont;i++){
        scanf("%f %f",&x,&y);
        labirinto->vet[i] = iniciarGrafo(x,y,i+1);
    }

    scanf("%d",&ncamara);
    labirinto->Ncamaras = ncamara;
    for(i=0;i<ncamara;i++){
        scanf("%d %d",&camara,&aberto);
        insereCamara(labirinto,camara-1,aberto);
    } 

    scanf("%d",&nSeg);
    labirinto->Nsegmentos = nSeg;
    for(i=0;i<nSeg;i++){
        scanf("%d %d",&c1,&c2);
        if(c1>-1 || c2 >-1) // considero os segmentos sem obstaculos
            insereSeg(labirinto,c1-1,c2-1);
    }

    scanf("%d",&inicial);
	processar(labirinto, inicial-1); // tira um para ficar na posição certa fo vet de "grafos"

    freeLab(labirinto);
    return 0;
}
	