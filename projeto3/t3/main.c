#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
		numero 0 50x30
		numero 1 10x50
		numero 2  
		numero 3 
		numero 4
*/


void printMatriz(int linha,int col,int **imagem){
	int i,j;
	for(i =0; i<linha;i++){
		for(j =0; j<col;j++){
			printf("%d",imagem[i][j]);
		} 
		printf("\n");
	}
}

void limpaZERO(int l, int c, int **matriz){
	int i,j;
	for(i=1;i<l-1;i++){
		for(j=0;j<c-1;j++){
			if(matriz[i][j] == 0 && (matriz[i+1][j] == 1  && matriz[i][j+1] == 1))
				matriz[i][j] = 1;
			if(matriz[i][j] == 1 && (matriz[i][j+1] == 0 && matriz[i][j+2] == 0 && matriz[i][j-1] == 0))
				matriz[i][j] = 0; 
		}
	}
}

int contMatriz(int l,int c,int **matriz){
	int i,j,sum=0;
	//printf("%d %d \n",l,c);
	for(i=l; i< l+50; i++){
		for(j=c;j< c+30;j++){
			if(matriz[i][j])
			sum += 1;			
		
		}
		
	}
	//printf("SOMA :%d\n\n",sum);
	return sum;
}

int indentificar(int x,int y, int **matriz){
	int num, i=0; // retorna numero 
	int contx=0,conty=0;
	num = contMatriz(x,y,matriz);
	
	if(num < 600 ){
	//	printf("ENTROU: 1\n\n");
		//*espaco = 23;  // numero para pular x posiçoes de coluans
		return 1;
	}else if(num < 950 & num  > 750){
	//	printf("ENTROU: 4\n\n");
		//*espaco = 46; 
		return 4;
	} else if(num < 720 & num > 600){
	//	printf("ENTROU: 7\n\n");
		//*espaco = 46; 
		return 7;
	} else if(num <1350 & num > 1250){
	//	printf("ENTROU: 8\n\n");
		//*espaco = 46; 
		return 8;
	} else if(num < 1150 && num > 1050){ // 2 3 e 5

		while(i++<30)
			if(matriz[x+i][y] == 1) // percorre a imagem na parte superior da esquerda para direita
				contx++;
		
		i=0;
		while(i++<30) // dpercorre a imagem pela esquerda de cima para baixo
			if(matriz[x+i][y+26] == 1)
			 	conty++; 
		if(contx > 25 && conty <25){    ////      5
			//printf("ENTROU: 5\n\n");
			//*espaco =46;
			return 5; // tudo ok
		}else{
		contx =0;
		i=0;
			while(i++<40)
			if(matriz[x+i][y] == 1) // percorre a imagem na parte superior da esquerda para direita
				contx++;
		
		i=0;
		conty =0;
			while(i++<40) // dpercorre a imagem pela esquerda de cima para baixo
				if(matriz[x+i][y+26] == 1)
			 		conty++;
			if(contx < 35 && conty < 35){
				//printf("ENTROU: 2\n\n");
				//*espaco =46;
				return 2; // 
			}else if(contx < 25 && conty > 30){
				//printf("ENTROU: 3\n\n");
				//*espaco =46;
				return 3; // 
			}
		}
	}else if(num < 1250 && num > 1150){ // 6 9 e 0
		contx =0;
		conty =0;
		i=0;
		while(i++<30)
			if(matriz[x+i][y] == 1) // percorre a imagem na parte superior da esquerda para direita
				contx++;
		
		i=0;
		while(i++<30) // dpercorre a imagem pela esquerda de cima para baixo
			if(matriz[x+i][y+26] == 1)
			 	conty++;
			
		if(contx > 25 && conty <25){      ////   //  6
			//printf("ENTROU: 6\n\n");
			//*espaco =46;
			//printf("%d %d\n", contx,conty);
			return 6; //
		}else {
			contx =0;
			conty =0;
			i=0;
			while(i++<40)
				if(matriz[x+i][y] == 1) // percorre a imagem na parte superior da esquerda para direita
					contx++;
		
			i=0;
			while(i++<40) // dpercorre a imagem pela esquerda de cima para baixo
				if(matriz[x+i][y+26] == 1)
				 	conty++;

			//	printf("%d %d\n", contx,conty);
			if(contx < 35 && conty >40){
				//printf("ENTROU: 9\n\n");
				//*espaco =46;
				return 9; //

			}else if(contx > 30 && conty >30){
				//printf("ENTROU: 0\n\n");
				//*espaco =46;
				return 0;
			}
		}
	}
	
}

int *achar(int l,int c,int **imagem){
	int i,j;
	int pular=46;
	int counter=0,aux;
	int *vet = (int*)malloc(sizeof(int) *(c/46));
	for(j=0;j<c;j++){
		for(i=0;i<l;i++){
			//pular =0;
			if(imagem[i][j] == 1 && (imagem[i][j+1] == 1 & imagem[i][j+3] ==1 ) && (imagem[i+1][j] & imagem[i+2][j])){ // tenta achar um ponto com um numero
				if(((i+49) < l) & ((j+15)< c)){ // impede do valor encontrar numeros nas bordas e perto delas
					aux = indentificar(i,j,imagem);
					vet[counter++] =aux;
					pular = 35;
					if(aux == 1)
						pular = 23;
					
					j= j+pular;
					//printf("        PULO :%d %d\n",j,pular);
					break;
				}					
			}	
		}
	}
	return vet;
}



int main(int argc, char* argv[]) {	
	int i,j;
	char *tipo, *nomeARQ;
	int tamLinhas, tamColunas, ampla; 

	tipo = (char *)malloc(sizeof(char)*2);
	nomeARQ= (char *)malloc(sizeof(char)*20); 

	scanf(" %s", nomeARQ);
	FILE *img;
	//struct pgm *imagem;
	img = fopen(nomeARQ, "r");

	if(img  == NULL){
		printf("ERROR AO LER O ARQUIVO");
		exit(1);
	} 

	fscanf(img, " %s", tipo);
	fscanf(img,"%d %d %d", &tamColunas,&tamLinhas,&ampla);

	int **imagem = (int **)malloc(sizeof(int *)*tamLinhas); // aloca espaço 
	for(i=0;i<tamLinhas;i++)
		imagem[i] = (int*)malloc(sizeof(int)*tamColunas); 

	for(i =0; i<tamLinhas;i++)
		for(j =0; j<tamColunas;j++)
			fscanf(img, "%d", &imagem[i][j]); //coloca a imagem em uma matriz de tamanho alocado 
		
	//printMatriz(tamLinhas,tamColunas,imagem);
	limpaZERO(tamLinhas,tamColunas,imagem); // diminui do ruido (nao totalmente e somente dentro do numero)
	//printf("\n");
	//printMatriz(tamLinhas,tamColunas,imagem);
	int *vetRESULTADO;
	vetRESULTADO=achar(tamLinhas, tamColunas,imagem);
	//printf("\n");
	//printf("\n%s\n%d %d\n%d\n", tipo, tamLinhas,tamColunas, ampla); 
	//printf("VETOR: \n");

	for(i=0;i<(tamColunas/46);i++)
		printf("%d",vetRESULTADO[i]);
	//achar(tamLinhas,tamColunas,imagem); 

	free(vetRESULTADO);
	free(tipo);
	free(nomeARQ);
	fclose(img);
  return 0;
}
