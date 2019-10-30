#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgm.h>
/*
		numero 0 50x30
		numero 1 10x50
		numero 2  
		numero 3 
		numero 4
*/

// captcha_01.pgm

/*void limpaZERO(int l, int c, int **matriz){
	int i,j;
	for(i=1;i<l-1;i++){
		for(j=0;j<c-1;j++){
			if(matriz[i][j] == 0 && (matriz[i+1][j] == 1  && matriz[i -1][j-1] == 1))
				matriz[i][j] = 1;
		}
	}

}  */

int main(int argc, char* argv[]) {
	char *tipo, *nomeARQ;
	int i,j;
	int tamLinhas, tamColunas, ampla; 
	//int **imagem;
	tipo = (char *)malloc(sizeof(char)*2);
	nomeARQ= (char *)malloc(sizeof(char)*20);
	scanf("%s", nomeARQ);
	FILE *img;
	//struct pgm *imagem;
	img = fopen(nomeARQ, "r");
	if(img  == NULL){
		printf("ERROR AO LER O ARQUIVO");
		exit(1);
	}
	fscanf(img, "%s", tipo);
	fscanf(img,"%d %d %d", &tamColunas,&tamLinhas,&ampla);

	int **imagem = (int **)malloc(sizeof(int *)*tamLinhas);
	for(i=0;i<tamLinhas;i++)
		imagem[i] = (int*)malloc(sizeof(int)*tamColunas); 

	for(i =0; i<tamLinhas;i++){
		for(j =0; j<tamColunas;j++){
			fscanf(img, "%d", &imagem[i][j]);
		}
	}
	printMatriz(tamLinhas,tamColunas,imagem);
//	limpaZERO(tamLinhas,tamColunas,imagem);
	printf("\n");
	printMatriz(tamLinhas,tamColunas,imagem);

	printf("\n%s\n%d %d\n%d", tipo, tamLinhas,tamColunas, ampla);
	
	
	fclose(img);
  return 0;
}