#include<stdlib.h>
#include <stdio.h>
#include <math.h>
#include <dctii.h>



/* 
o calculo e a somatoria da muplicação do vetor na posição j(n), com o cosseno
de pi(nesse caso usei pi da biblioteca math, pois usar 3,14 da erro) sobre o tamnho do vetor
vezes o i(k) vezes somatoria de j(n) e 1/2.
*/

// recebe o vetor de entrada, o vetor de saida o tamanho do vetor
void dct(double *ino,double *out,int size){
    int i,j;
    double temp; // auxiliar 
    for(i=0;i<size;i++){
			temp =0; // zera 
        for(j=0;j<size;j++){
          	temp += ino[j] * cos(M_PI/size * i * (j + 0.5));
        }
    out[i] = temp; // 
   } 
}