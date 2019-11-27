#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "sudoku.h"


/*
eu confiro se tem alguma posição só se pode colocar um elemento
assim eu fico colocando os elmentos, ele confere linha, coluna e bloco
caso só há uma possibilidade ele coloca esse elemento
*/

// cria a aloca matriz
char **criarMat(){
	if(TAM <=0){ printf("erro TAManho da matriz"); return NULL;}
	int i;
	char **matriz = (char**)calloc(TAM,sizeof(char*));
	for(i =0; i<TAM;i++)
		matriz[i] = (char*)calloc(TAM,sizeof(char));
	
	return  matriz;
}

// ler Sudoku
int lerSudoku(char**matriz ){
	if(!matriz) return ERRO_MATRIZ;
	int i,j;
    char op;

	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			scanf(" %c", &op);
            if(op != '.') 
                matriz[i][j] =  op;
        }
    }
	return SUCESSO;
}

// printar matriz do sudoklu
int printSudoku(char** mat){
	if(!mat) return ERRO_MATRIZ;
	int i,j;
	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			printf("%c", mat[i][j]);
		}
	printf("\n");
	}
	return SUCESSO;
}


void freeSudoku(char**p){ // dar free no sudoku
	int i;
	for(i=0;i< TAM;i++)
		free(p[i]);

	free(p); // dar free na matriz toda
}


void Conferelinha(char**p, int y, int* hashTable){ // confere linha
	int i;
	for(i =0;i< TAM;i++)
        hashTable[(int)p[i][y]]++; // confere por linha
}

void Conferecoluna(char**p, int x, int* hashTable){
	int i;
	for(i =0;i< TAM;i++)
        hashTable[(int)p[x][i]]++; // confere por coluna
}

void Conferebloco(char **mat, int x,int y,int *hashTable){
	int i,j;
 	for(i = x; i < (x+4); i++) // confere o grupo 
		for(j =y; j < (y+4) ;j++)
			hashTable[(int)mat[i][j]]++;
}

// confore a posição se tem uma possibiblidade
char *confere(char**mat,int x, int y, int *pos){
    int i,j,num=0;
	int posi = (x/4)*4;
	int posj = (y/4)*4; // para achar posição inicial do quadrado do sudoku

    int *hashTable= (int*)calloc(71,sizeof(int));
    char *letra= (char*)malloc(sizeof(char));;

	Conferelinha(mat,y,hashTable); // confere linha
	Conferecoluna(mat,x,hashTable); // confere coluna 
	Conferebloco(mat,posi,posj,hashTable); // confere bloco
    
    for(i=48;i<58;i++){
        if(!hashTable[i]){
            letra = (char*)realloc(letra,(++num)*sizeof(char));
            letra[num-1] = i;
        }
    }
   
    for(i=65;i<71;i++){
        if(!hashTable[i]){
            letra = (char*)realloc(letra,(++num)*sizeof(char)); // caso ha mais possibilidades
            letra[num-1] = i;
        }
    }
    *pos = num;
    return letra;
}

int Sudoku(char **mat){
    if(!mat) return ERRO_MATRIZ;
    int i,j, quant=1,flag =1;
    char *novo;

    while(flag){ // continuar até todos os espaços estiverem cheios
    	flag = 0;
		for(i= 0; i <TAM;i++){
			for(j =0; j<TAM ;j++){
				if(!mat[i][j]){
                    novo = confere(mat,i,j,&quant);
                    if(quant == 1){
                        mat[i][j] = novo[0];
                    } 
                    flag = 1;
                }
	        }	

	    }
    }

    return SUCESSO;
}


