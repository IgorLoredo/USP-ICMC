#include<stdlib.h>
#include <stdio.h>
#include <math.h>
#include <dctii.h> // biblioteca com o comando

int main(){
    int i;
    int tam;
    double *vetorIn = NULL;
    double *vetorOut = NULL; // aponta para null
    scanf("%d",&tam); // pega o tamanho do vetor
    vetorIn = (double*)malloc(sizeof(double)*tam);
    vetorOut = (double*)malloc(sizeof(double)*tam); //aloca espaço

    for(i=0;i<tam;i++)
        scanf("%lf",&vetorIn[i]);

    dct(vetorIn,vetorOut,tam); // tranforma o vetor de entrada

    for(i=0;i<tam;i++)
        printf("%lf\n",vetorOut[i]);
    
    free(vetorIn);
    free(vetorOut); // libera espaco 
    return 0;
}