#include <stdio.h>
#include <stdlib.h>
#include <esparsa.h>

int main(){
    char op;
    int x,y,elem,flag =0;
    scanf("%c",&op); // opção de operação
    scanf("%d %d %d",&x,&y,&elem); // primeira entrada tem o tamanho do elemento
    
    ESPARSA_MATRIZ *matriz1 = criarMatriz(y,elem,0);
    while(flag == 0){ // coloca até flag = 1
        scanf("%d %d %d",&x,&y,&elem);
        if(x < 0)
            flag++; // caso x = -1 quebra lanço
        else 
            addMatriz(matriz1,x,y,elem); // caso elemento diferente de -1
    }

    ESPARSA_MATRIZ *matriz2 = criarMatriz(y,elem,0); // cria outra matriz com o tamanho dando antes
    
    while(!feof(stdin)){ // coloca até acaba tudo 
        scanf("%d %d %d ",&x,&y,&elem);
        addMatriz(matriz2,x,y,elem);
    }

    if(op == 'A'){
        ESPARSA_MATRIZ *result = somaMatriz(matriz1,matriz2);
      imprimir_matriz(result);
      freeMatriz(result);
    }else if(op == 'M'){
        ESPARSA_MATRIZ *result = multMatriz(matriz1,matriz2);
        imprimir_matriz(result);
        freeMatriz(result);   
   }
        
    freeMatriz(matriz1); // free em tudo
    freeMatriz(matriz2);

    return 0;
}
