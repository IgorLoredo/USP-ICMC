#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgm.h>

/*
	utilizei a contagem de pontos(quantidade de 1 dentro de cada numero) e simetrias e pontos que diferenciam 
	cada numero um do outro.
	comecei a contar de forma geral a quantidades de uns toda vez que encontrava um novo numero
	com isso fazia separacao de cada numero de acordo com a quantidade de uns que que tinha>
	alguns numeros ja tinham certa qunantidade de numeros proprias:
	1 --  500
	4 -- 900
	7 -- 700
	8 -- 1300
	ja os outros tinham a mesma quantidade que outros:
	2,3 e 5 - 1100
	6 9 e 0 - 1200
	nisso eu separo pelas categorias depois eu separo pela simetria de cada uma usando um contador lateral
	faço tudo isso fazenodo contagens e usando intervalos (pois há presença de ruidos minimos)
	obs: há partes  comentadas no codigo que não fazem parte da explicão porque eu sei essas partes para debugar o codigo,
*/

void printMatriz(int linha,int col,int **imagem){
	int i,j;
	for(i =0; i<linha;i++){
		for(j =0; j<col;j++){
			printf("%d",imagem[i][j]);
		} 
		printf("\n");
	}
} // só para nivel de debugar a matriz

void limpaZERO(int l, int c, int **matriz){
	int i,j;
	for(i=0;i<l-1;i++){
		for(j=0;j<c-1;j++){
			if(matriz[i][j] == 0 && (matriz[i+1][j] == 1  && matriz[i][j+1] == 1))
				matriz[i][j] = 1;
			if(matriz[i][j] == 1 && (matriz[i][j+1] == 0 && matriz[i][j+2] == 0 && matriz[i][j-1] == 0))
				matriz[i][j] = 0; 
		}
	}
}  // faz a limpeza basica dos ruidos, apesar que estar bem eficente

int contMatriz(int l,int c,int **matriz){ 
	int i,j,sum=0;
	//printf(" contar matriz :   %d %d \n",l,c);
	for(i=l; i< l+50; i++){
		for(j=c;j< c+30;j++){
			//printf(" %d", matriz[i][j]);
			if(matriz[i][j])
				sum += 1;					 
		} 
		//printf("\n");
	}
	//printf("SOMA :%d\n\n",sum);
	return sum; // contador de 1 na matriz
}

void contador(int num,int x,int y,int *contx, int *conty, int **matriz){
	int i=0;
	*contx =0;
	*conty =0;
	while(i++<num){
		if(matriz[x+i][y] == 1) // percorre a imagem na parte superior da esquerda para direita
			*contx += 1;
	}
		i=0;

	while(i++<num){ // dpercorre a imagem pela esquerda de cima para baixo
	if(matriz[x+i][y+26] == 1)
			*conty+=1;
		}
	
}


int indentificar(int x,int y, int **matriz){
	int num, i=0; // retorna numero 
	int contx=0,conty=0; // contadores laterias
	num = contMatriz(x,y,matriz); // conta quantos 1 tem tem no espaco que foi encontrado o numero
	//printf("     entrou na id:  %d %d", x,y);
	if(num < 600 ){ // quantidade unica do numero 1 - 700
		return 1;
	}else if(num < 950 & num  > 750){ // intervalo entre o numero 4 -- 900
		return 4;
	} else if(num < 720 & num > 600){ // intervalo entre o numero 7 -- 1200
		return 7;
	} else if(num <1350 & num > 1250){ // intervalo entre o numero 8 -- 1300
		return 8;
	} else if(num < 1150 && num > 1050){ // // intervalo dos numeros 2,3 e 5

		contador(30,x,y,&contx,&conty,matriz); // conta quantos numeros tem nas laterias até 30 posições abaixo

		if(contx > 25 && conty <25){   // o numero  5 tem um difença nas laterias(decendo 30 linhas), nisso dar para difenciar do resto (2 e 3)
			return 5; // tudo ok
		}else{
			/*
			o 2 e 3 nao dar para diferenciar pela contagem acima, mas se descer 40 linhas dar para fazer isso
			pois o 3 tem dois espaços com zeros na lateral esquerda e nada na direita e o 2 tem um na esquerda e outra na direnta
			*/
			contador(40,x,y,&contx,&conty,matriz); // conta quantos numeros tem nas laterias até 40 posições abaixo

			if(contx < 35 && conty < 35){ // usei 35 pq pode haver ruidos n eliminados nas laterais
				return 2; //      2  
			}else if(contx < 25 && conty > 30){
				return 3; // 
			}
		}
	}else if(num < 1250 && num > 1150){ // intervalo dos numeros 6 9 e 0
		/*
		para o 6, 9 e 0 segue a mesma logica de antes
		pecorre as laterias contando e armazenado a contagem
		*/
		contador(30,x,y,&contx,&conty,matriz); // conta quantos numeros tem nas laterias até 30 posições abaixo
		if(contx > 25 && conty <25){      //o 6 tem um espaço na lateral esquerda 
			return 6; 
		}else {
			contador(40,x,y,&contx,&conty,matriz); // conta as laterias 40 linhas para abaixo
				//printf("%d %d\n", contx,conty);
			if(contx < 35 && conty >35){ // o numero 9 tem um espaço do lado esquerdo e nenhum do lado direito
				return 9; //

			}else if(contx > 30 && conty >30){ // o 0  tem espaços nas laterais
				return 0;
			}
		}
	}
	
}

void achar(int l,int c,int **imagem, int *vet){
	int i,j;
	int pular=46; // uso pra pular posições para frente depois de achar um numero
	int counter=0,aux=0;
	int contx,conty; // contadores laterais

	for(j=0;j<c-4;j++){
		for(i=0;i<l-4;i++){
			//pular =0;
			if(imagem[i][j]){ // tenta achar um ponto com um numero
				if(((i+40) < l) && ((j+10)< c)){ // impede do valor encontrar numeros nas bordas e perto delas
					contador(10,i,j,&contx,&conty,imagem); // conta para baixo se numeros
					//printf("cotandor   %d %d\n", contx,conty);
					if(contx > 7){ // uso só um contador da lateral
						
						aux = indentificar(i,j,imagem); // funçaõ de identificar 
						//printf("                       aux :%d\n", aux);
						vet[counter++] =aux; // para o vetor por referencia 
						if(aux == 1){
							pular = 10;  // uso isso pq o 1 tem o tamanho 10 
						}else {
							pular = 35;
						}
						j= j+pular; // acrecenta o pular para o j, assim o contador vai para frente
						//	printf("        PULO :%d %d\n",j,pular);
						//break;
					}
					
				}					
			}	
		}
	}

}
