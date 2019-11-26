#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sudoku.h>

// cria a aloca matriz
char **criarMat(int tam){
	if(tam <=0){ printf("erro tamanho da matriz"); return NULL;}
	int i;
	char **matriz = (char**)calloc(tam,sizeof(char*));
	for(i =0; i<tam;i++)
		matriz[i] = (char*)calloc(tam,sizeof(char));
	
	return  matriz;
}

// ler Sudoku
int lerSudoku(char**matriz,int tam ){
	if(!matriz) return ERRO_MATRIZ;
	int i,j;
	for(i=0;i<tam;i++)
		for(j=0;j<tam;j++)
			scanf(" %c", &matriz[i][j]);
	return SUCESSO;
}


int printSudoku(char** mat,int tam){
	if(!mat) return ERRO_MATRIZ;
	int i,j;
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			printf("%c", mat[i][j]);
		}
	printf("\n");
	}
	return SUCESSO;
}



