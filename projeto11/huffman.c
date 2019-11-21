#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>

// funções da pilha. todas encapsuladas
PILHA *criarPilha(){
    PILHA *new  = (PILHA*)calloc(1,sizeof(PILHA));
    new->vet = (int*)calloc(1,sizeof(int));
    return new;
} // cria pilha 

void empilhar(PILHA *p, int elem){
    p->vet = (int*)realloc(p->vet,sizeof(int)* (p->cap)+1);
    p->vet[p->cap++] =  elem;
} // empilhar elementos na pilha

int desempilhar(PILHA*p){
    int aux =  p->vet[p->cap];
    p->vet = (int*)realloc(p->vet,sizeof(int)*(--p->cap));
    return aux;
} // desempilha elementos e retona eles

int *vetpilha(PILHA *p){ // faz a pilha virar um vetor
    int *new = (int*)calloc(p->cap+1,sizeof(int));
    int i;
    for(i=0;i<p->cap;i++)
        new[i] = p->vet[i];

    return new;
}

// funções huffamn
treeHuffamn *criarHuffman(int tam){
    treeHuffamn *new = (treeHuffamn*)calloc(1,sizeof(treeHuffamn));
    new->tam = tam;
    return new;
} // criar root e o tamanho original da palavra

// criei varias funções encapsuladas 

 //Utiliza o Bubblesort para organizar os vetores dos simbolos e de suas frequencias. encapsulada
void ordenaVetor(int size, NODE** vet){
    int i,j;
    NODE *temp;
    for(i=0;i>size-1;i++){
        for(j=0;j<size;j++){
            if(vet[j]->freq < vet[j+1]->freq){
                temp =  vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
    }
} // algoritmo de ordenamento para ordenar a frenquencia

int *criarFrequencia(char *tabela){ // encapsulada
    int i;
    int *fren = (int*)calloc(127,sizeof(int)); // quantidade de elementos da tabela ascii
    for(i=0;i<strlen(tabela);i++){
        fren[tabela[i]] ++; 
        //printf("%d ",tabela[i]);
    }
    return fren;
}

NODE **criarfolhas(char *tabela, int *contador){ //encapsulada
    int i,cont=0;
    printf("tamanho que entrou a palavra %ld \n",strlen(tabela));
    int *frequencia = criarFrequencia(tabela);// criar frenquencia
    
    NODE **vetnode = (NODE**)calloc(1,sizeof(NODE*)); // vetor com os nodes que vão ser gerados
    for(i=0;i<127;i++){
        if(frequencia[i] > 0){
            NODE *novo = (NODE*)calloc(1,sizeof(NODE));
            novo->freq = frequencia[i];
            novo->letra = (char)i;
            novo->flag = 1;
            vetnode = (NODE**)realloc(vetnode,sizeof(NODE*)*cont+1); // criar folha coloca no vetor
            vetnode[cont++] = novo;
        }
    }
    ordenaVetor(cont,vetnode); // ordena as folhas
   /* for(i=0;i<cont;i++){
        printf("\nletra %c frequencia %d\n",vetnode[i]->letra,vetnode[i]->freq);
    } */

    free(frequencia);
    *contador = cont;
    return vetnode;
}

NODE *criarArvore(NODE **vet,int cont){
    if(vet == NULL) return NULL;
    // o i começa com cont e assim vai ficar com 2 nodes menor que a frequencia
    int i = cont;
    while(i>1){
        NODE *new = (NODE*)calloc(1,sizeof(NODE));
        new->freq = vet[0]->freq + vet[1]->freq;
        new->esq = vet[0];
        new->dir = vet[1];
        i--;
        ordenaVetor(i,vet);
        //vet = (NODE**)realloc(vet,sizeof(NODE*)*i)
    }
    NODE *raiz = vet[0];
    return  raiz;
}


