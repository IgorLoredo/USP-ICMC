#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgm.h>


// cometarios resolução no arquivo pgm.c

int main(int argc, char* argv[]) {	
	int i,j;
	char *tipo, *nomeARQ;
	int tamLinhas, tamColunas, ampla; // tamanho das linhas, colunas e amplitude 

	tipo = (char *)malloc(sizeof(char)*3);
	nomeARQ= (char *)malloc(sizeof(char)*20); // faz o malloc dos ponteiros 

	scanf(" %s", nomeARQ); // pega o nome do arquivo
	FILE *img;  // cria o arquivo

	img = fopen(nomeARQ, "r");

	if(img  == NULL){
		printf("ERROR AO LER O ARQUIVO"); 
		exit(1);
	} 
  
	fscanf(img, " %s", tipo);
	fscanf(img,"%d %d %d", &tamColunas,&tamLinhas,&ampla);

	int **imagem = (int **)malloc(sizeof(int *)*tamLinhas); // aloca espaço da imagem
	for(i=0;i<tamLinhas;i++)
		imagem[i] = (int*)malloc(sizeof(int)*tamColunas); 

	for(i =0; i<tamLinhas;i++)
		for(j =0; j<tamColunas;j++)
			fscanf(img, "%d", &imagem[i][j]); //coloca a imagem em uma matriz de tamanho alocado 

	limpaZERO(tamLinhas,tamColunas,imagem); // diminui do ruido (nao totalmente, 90% por ai)
	
	int *vetRESULTADO = NULL;
	vetRESULTADO = (int*)malloc(sizeof(int)*((tamColunas/46)+1)); // aloca espaco para armazenar os vetores, como há um padrão no tamanhod a imagem e é so dividir por 46
	achar(tamLinhas, tamColunas,imagem,vetRESULTADO); // acha os numeros 

	for(i=0;i<((tamColunas/46));i++)
		printf("%d",vetRESULTADO[i]); // mostra os resultados

	for(i=0;i<tamLinhas;i++) // libera a memoria
		free(imagem[i]);
	free(imagem);
	free(vetRESULTADO);
	free(tipo);
	free(nomeARQ);
	fclose(img);
  return 0;
}


