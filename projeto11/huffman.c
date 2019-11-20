#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>

treeHuffamn *criarHuffman(int tam){
    treeHuffamn *new = (treeHuffamn*)calloc(1,sizeof(treeHuffamn));
    new->tam = tam;
    return new;
} // criar root e o tamanho original da palavra

// crei varias funções encapsuladas 

 //Utiliza o Bubblesort para organizar os vetores dos simbolos e de suas frequencias. encapsulada
void ordenaVetor(int size, NODE** vetLeaf){
    int i,j;
    NODE *temp;
    for(i=size-1;i>=0;i--){
        for(j=0;j<=i;j++){
            if(vetLeaf[j]->freq < vetLeaf[j+1]->freq){
                temp =  vetLeaf[j];
                vetLeaf[j] = vetLeaf[j+1];
                vetLeaf[j+1] = temp;
            }
        }
    }
} // algoritmo de ordenamento para ordenar a frenquencia

int *criarFrequencia(char *tabela){ // encapsulada
    int i;
    int *fren = (int*)calloc(127,sizeof(int)); // quantidade de elementos da tabela ascii
    for(i=0;i<=strlen(tabela);i++){
        fren[(int)tabela[i]] +=1; 
    }
    return fren;
}

NODE **criarfolhas(char *tabela, int *contador){ //encapsulada
    int i,cont;
        
    int *frequencia = criarFrequencia(tabela);// criar frenquencia
    
    NODE **vetnode = (NODE**)malloc(sizeof(NODE*)); // vetor com os nodes que vão ser gerados
    for(i=0;i<strlen(tabela);i++){
        if(frequencia[i] > 0){
            NODE *novo = (NODE*)malloc(sizeof(NODE));
            novo->freq = frequencia[i];
            novo->letra = (int)frequencia[i];
            vetnode = (NODE**)realloc(vetnode,sizeof(NODE*)*cont+1); // criar folha coloca no vetor
            vetnode[cont++] = novo;
        }
    }
    ordenaVetor(cont,vetnode); // ordena as folhas
    for(i=0;i<cont;i++){
        printf("letra %c frequencia %d",vetnode[i]->letra,vetnode[i]->freq);
    }
    free(frequencia);
    *contador = cont;
    return vetnode;
}

NODE *criarAvore(NODE **vet,int cont){
    if(vet == NULL) return NULL;

}
