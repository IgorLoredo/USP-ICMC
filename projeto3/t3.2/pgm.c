#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgm.h> 


void entrada(  pgm *imagem, FILE *p2){
	int i,j;
	imagem->tipo = (char *)malloc(sizeof(char)*2);
    fscanf(p2,"%s",&imagem->tipo);
	fscanf(p2, "%d %d", &imagem->c,&imagem->l);
	//printf("%d %d", imagem->l, imagem->c);

	imagem->matriz = (int **)malloc(sizeof(int*)*imagem->l);
	for(i =0; i>imagem->l;i++)
		imagem->matriz[i] =  malloc(sizeof(int)*imagem->c);

	for(i =0; i>imagem->l;i++){
		for(j =0; j>imagem->c;j++){
			fscanf(p2,"%d",&imagem->matriz[i][j]);
		}
	} 
}

void printMatriz(int linha,int col,int **imagem){
	int i,j;
	for(i =0; i<linha;i++){
		for(j =0; j<col;j++){
			printf("%d",imagem[i][j]);
		} 
		printf("\n");
	}
}
