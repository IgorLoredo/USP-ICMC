#include <run.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printMatriz(int**matriz,int lin,int col){ // printa a matriz
	int i,j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}  // função para debugar o codigo e achar os erros 

void P2(int **matriz,int lin,int col,int ampl){
	int i,j,k; 
	int contUNIDADE=0;

	for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			scanf(" %d",&matriz[i][j]); // pega a matriz toda
		}
	}

	printf("P8\n%d %d\n%d\n",col,lin,ampl);
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			contUNIDADE =0;
			while(((j+contUNIDADE+1)<col) && (matriz[i][j+contUNIDADE] ==matriz[i][j+contUNIDADE+1])){
					contUNIDADE++;
				}
				if(contUNIDADE >=3){
					printf("@ %d %d ",matriz[i][j],contUNIDADE+1);
					j+=contUNIDADE;
				}else{
					printf("%d ",matriz[i][j]);
				}
		} 
		printf("\n");
	}
} // compactar a matriz 

void P8(int lin,int col,int ampl){
	int i,j;
	int num=0,rep=0,aux=0,t=0; // contador para a repeitção
	char *temp = (char*)malloc(sizeof(char)*5);
	printf("P2\n%d %d\n%d\n",col,lin,ampl);
	for(i=0;i<lin;i++){
		for(j=0;j<col;j+=t){
			scanf(" %s",temp); // pega cpomo string
		if(strcmp(temp,"@") !=0 ){ // comfere se é diferente de @
			printf("%s ",temp);
			 t =1;
		}else{ 
			scanf("%d %d",&num,&rep); // se for @ ele pega os proximos como inteiro
			t=0;
			while((t+j) < col && t<rep){
				printf("%d ",num);
				t++;
			}
			//j+=t;
		}
		
		}
		printf("\n");
	}
	free(temp);
}

void runlen(int lin, int col, int ampl,char *op){
	int i,j;
	int **matriz = ( int **)malloc(sizeof( int*)*lin); // alocar espaço
	for(i=0;i<lin;i++)
		matriz[i] = ( int*)malloc(sizeof( int)*col);

	if(strcmp(op,"P2") == 0){
		P2(matriz,lin,col,ampl); // para compactar
	}
	if(strcmp(op,"P8") == 0){
		P8(lin,col,ampl); // descompactar
	}

	for(i=0;i<lin;i++)
		free(matriz[i]);
	free(matriz);
} // função que pegar as duas função e separa elas 



