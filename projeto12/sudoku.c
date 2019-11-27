#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "sudoku.h"

// cria a aloca matriz
char **criarMat(int tam){
	if(tam <=0){ printf("erro tamanho da matriz"); return NULL;}
	int i;
	char **matriz = (char**)malloc(tam*sizeof(char*));
	for(i =0; i<tam;i++)
		matriz[i] = (char*)calloc(tam,sizeof(char));
	
	return  matriz;
}

// ler Sudoku
int lerSudoku(char**matriz,int tam ){
	if(!matriz) return ERRO_MATRIZ;
	int i,j;
    char op;
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			scanf(" %c", &op);
            if(op != '.') 
                matriz[i][j] =  op;

        }
    }
	return SUCESSO;
}


int printSudoku(char** mat,int tam){
	if(!mat) return ERRO_MATRIZ;
	int i,j;
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
            if(mat[i][j])
			printf("%c", mat[i][j]);
		}
	printf("\n");
	}
	return SUCESSO;
}

/*int quadrado(char**mat,int x,int y,int *vet){
    int i,j,num;
	int flagQuadrado = 15; // seta 16 para todos os flag
	int posi = (x/4)*4;
	int posj = (y/4)*4;

    for(i = posi; i < (posi+4); i++){
		for(j =posj; j < (posj+4) ;j++){
			if(mat[i][j] != '!'){
                num = isdigit(mat[i][j]);
				if(num){ // confere se é um numero 
					vet[mat[i][j]-48]++;
				}
				else{ 
					vet[mat[i][j]-55]++;
				}

			
			}else{
                flagQuadrado--;
            }
		}
	}

    return flagQuadrado;
}

int linha(char**mat,int x,int y,int *vet){
    int i,j,num;
	int flagLinha = 15;
	int posi = (x/4)*4;
	int posj = (y/4)*4;
    // confere a linha 
	for(i=0;i < 16 ;i++){ 
        if(mat[i][y] != '!'){
            num = isdigit(mat[i][y]) ;
		    if(num ){ // confere se é um numero 
				vet[mat[i][y]- 48]++;
			}
			else {
				vet[mat[i][y]-56]++;
				
			}
		
		}else{
            flagLinha--;
        }
	}
    return flagLinha;
}


int coluna(char**mat,int x,int y,int *vet){
    int i,j,num;
	int flagColuna = 15;
	int posi = (x/4)*4;
	int posj = (y/4)*4;
	    //printf("%d \n",x);
	for(j=0 ; j < 16; j++){
        if(mat[x][j] != '!'){
            num  = isdigit(mat[x][j]);
			if( num ){ // confere se é um numero 
				vet[mat[x][j] - 48]++;
			}
			else {
                // printf("j %d %c \n",j,mat[x][j]);
				vet[mat[x][j] - 54]++;
				
			}
		}else{
            flagColuna--;
        }
		
	}
    return flagColuna;
}


int conferer(char**mat,int x,int y, int *pos){
	int i,j,num;
	int flagQuadrado = 0; // seta 16 para todos os flag
	int flagColuna = 0;
	int flagLinha = 0;
	int index=-1;
	int posi = (x/4)*4;
	int posj = (y/4)*4;

	int *vet = (int*)calloc(16,sizeof(int));
	flagLinha = linha(mat,x,y,vet);
    flagColuna = coluna(mat,x,y,vet);
    flagQuadrado = quadrado(mat,x,y,vet);

	//printf("%d %d %d\n",flagLinha,flagColuna,flagQuadrado);
	if(flagLinha <= 1 || flagColuna <= 1 || flagQuadrado <= 1){
		//printf("entrou");
		// acha o numero com tem a maior possibilidade de ser
		for(i =0;i<16;i++){
			if(vet[i] > index){
				index = vet[i];
				*pos = i;
			}	
		}
		return 1;
	} else {
		return 0;
	}

}

int Sudoku(char **mat,int tam){
	if(!mat) return ERRO_MATRIZ;
	int i,j;
	int pos = 1,num,flag = 1;
	char *vetResposta = (char*)malloc(sizeof(char)*15);

	for(i = 0; i < tam;i++){
		if(i < 10)
			vetResposta[i] = (char)(i+48);
		else
			vetResposta[i] = (char)(i+55);
	}

	while(flag){
		pos = 1;
		for(i= 0; i <tam && pos ;i++){
			for(j =0; j<tam && pos;j++){
				if(mat[i][j] == '!'){
					num = conferer(mat,i,j,&pos);
						if(num == 1){ 
							//printf("entrou %d %d j%c\n",i,j,mat[i][j]);
							mat[i][j] = vetResposta[pos]; 
                            printf("pos: %d  i %d j %d\n",pos,i,j);
							pos =0;
						}
				}
			}
			if( i >= tam-1 && j >= tam-1 ){
				flag = 0;
			} 
			

		}
	}


	return SUCESSO;
} */



char *confere(char**mat,int x, int y, int *pos){
    int i,j,num=0;
	int posi = (x/4)*4;
	int posj = (y/4)*4;
    int *hashTable= (int*)calloc(128,sizeof(int));
    char *letra= NULL;
    char op;

    for(j =0;j< 16;j++){
        hashTable[(int)mat[x][j]]++; // confere por coluna
    }
    for(i =0;i< 16;i++){
       
        hashTable[(int)mat[i][y]]++; // confere por linha
    }

    for(i = posi; i < (posi+4); i++){
		for(j =posj; j < (posj+4) ;j++){
           
			hashTable[(int)mat[i][j]]++;
		}
	}

    for(i=48;i<58;i++){
        if(!hashTable[i]){
            num++;
            letra = (char*)realloc(letra,sizeof(char)*num);
            letra[num-1] = i;
        }
    }
    
    for(i=65;i<71;i++){
        if(!hashTable[i]){
            num++;
            letra = (char*)realloc(letra,num*sizeof(char));
            letra[num-1] = i;
        }
    }

    *pos = num;
    return letra;
}

int Sudoku(char **mat,int tam){
    if(!mat) return ERRO_MATRIZ;
    int i,j, quant=1,flag =1;
    char *novo;

    while(flag++ < 1000){

        //flag = 0;
		for(i= 0; i <tam;i++){
			for(j =0; j<tam ;j++){
				if(!mat[i][j]){
                   
                    novo = confere(mat,i,j,&quant);
                    if(quant == 1){
                        mat[i][j] == novo[0];
                        
                    } 
                   // flag = 1;
                }
	        }	

	    }
    }

    return SUCESSO;
}


