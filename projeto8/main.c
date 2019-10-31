#include <stdlib.h>
#include <stdio.h>
#include <maze.h>

int main(){
    int i;
    float x,y;
    int npont,ncamara,nSeg;
    scanf("%d",&npont);
    LAB *labirinto = iniciar_lab(npont);

    for(i=0;i<npont;i++){
        scanf("%f %f",&x,&y);
        labirinto->vet[i] = iniciarGrafo(x,y);
    }
/*
    for(i=0;i<ncamara;i++){

    } */

    free(labirinto);
    return 0;
}
 