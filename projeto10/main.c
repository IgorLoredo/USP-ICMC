#include <stdio.h>
#include <stdlib.h>
#include "esparsa.h"



int main(){
    char op;
    ESPARSA_MATRIZ *matriz1 = criarMatriz(10,10,3);
    addMatriz(matriz1,1,1,2);
    printf("%d\n",getMatriz(matriz1,1,1));


    freeMatriz(matriz1);
    //scanf("%c",&op);
    return 0;
}
