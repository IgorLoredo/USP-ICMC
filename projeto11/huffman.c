#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>


// funções da lista encadeada
LISTA *criarLista(){
  LISTA *new  = (LISTA*)calloc(1,sizeof(LISTA));
 return new;
}

void addLista(LISTA *list, NODE *elem){ // adicionar elementos na lista
    int pos=0;
    ELEM *new = (ELEM*)calloc(1,sizeof(ELEM)); // cria elemento da lista
    new->no = elem; // adiciona no elemento
    ELEM **p;
    p= &list->first;

    while(*p && elem->freq > (*p)->no->freq) {
        (p = &(*p)->prox);
        pos++;
    }
	*p = new;
    new->prox = *p;
    if (pos == list->tam) list->last = new; 
    list->tam++;
}

void removeLista(LISTA *list, int pos){ // remover elemento na lista
    ELEM *p,*prev;
    prev = NULL;
    p = list->first;
    int cont=0;
    while(cont < pos){ //  procura a posição
        prev = p;
		p = p->prox;
		cont++;
    }

    if (prev) { // faz a remoção, no caso eu n dou free pq vou ta apontando para o elemento ja feito
		prev->prox = p->prox;
		if (list->last == p) list->last = prev;
	} else list->first = p->prox;
    //free(p);
	list->tam--;

}

// freee na lista
void freeLista(LISTA *list) {
	ELEM *p, *aux;
	p = list->first;

	while (p) {
		aux = p->prox;
		free(p);
		p = aux;
	}
	free(list);
}

// funções da pilha. todas encapsuladas
PILHA *criarPilha(){
    PILHA *new  = (PILHA*)calloc(1,sizeof(PILHA));
    new->vet = (int*)calloc(1,sizeof(int));
    return new;
} // cria pilha 

void empilhar(PILHA *p, int elem){
    p->vet = (int*)realloc(p->vet,sizeof(int)* (p->cap)+1);
    p->vet[p->cap] =  elem;
    p->cap++;
} // empilhar elementos na pilha

int desempilhar(PILHA*p){
    int aux =  p->vet[p->cap];
    p->vet = (int*)realloc(p->vet,sizeof(int)*(--p->cap));
    return aux;
} // desempilha elementos e retona eles

int *vetpilha(PILHA *p){ // faz a pilha virar um vetor
    int *new = (int*)calloc(p->cap,sizeof(int));
    int i;
    for(i=p->cap-1;i>=0;i++)
        new[i] = p->vet[i];

    return new;
}

void freePilha(PILHA*p){
    free(p->vet);
    free(p);
} // dar free na matriz


// criar matriz pilha
Dicio *criarMatrizPilha(){
    return (Dicio*)calloc(1,sizeof(Dicio));
}


void DFS(NODE *no,PILHA *p,Dicio *Pilhamatriz){
    if(no &&no->flag == 1){
        int *vet = vetpilha(p);
        
    }else{
        if(no->esq){
            empilhar(p,0);
            DFS(no->esq,p,Pilhamatriz);
        }else if(no->dir){
            empilhar(p,1);
            DFS(no->dir,p,Pilhamatriz);
        }
    }

    desempilhar(p);
}


 //Utiliza o Bubblesort para organizar os vetores dos simbolos e de suas frequencias. encapsulada
void ordenaVetor(int size, int *vet){
    int i,j;
    int temp;
    for(i=0;i>size-1;i++){
        for(j=0;j<size;j++){
            if(vet[j] > vet[j+1]){
                temp =  vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
    }
} // algoritmo de ordenamento para ordenar a frenquencia


// funções huffman
treeHuffamn *criarHuffman(int tam){
    treeHuffamn *new = (treeHuffamn*)calloc(1,sizeof(treeHuffamn));
    new->tam = tam;
    return new;
} // criar root e o tamanho original da palavra

// criei varias funções encapsuladas 
int *criarFrequencia(char *tabela){ // encapsulada
    int i;
    int *fren = (int*)calloc(127,sizeof(int)); // quantidade de elementos da tabela ascii
    for(i=0;i<strlen(tabela) || (tabela[i] == '\0')  ;i++){
        fren[tabela[i]]++; 
    }
    return fren;
}

LISTA *criarfolhas(char *tabela){ //encapsulada
    int i=0;
    int *frequencia = criarFrequencia(tabela);// criar frenquencia
    LISTA *listaFolhas = criarLista();
   // printf("%d",frequencia[i]);
    for(i=0;i<127;i++){
       // printf("%d",frequencia[i]);
        if(frequencia[i] > 0){
         //  printf("%c %d fre %d\n",i,i,frequencia[i]);
            NODE *novo = (NODE*)calloc(1,sizeof(NODE));
            novo->freq = frequencia[i];
            novo->letra = (char)i;
            novo->flag = 1;
            addLista(listaFolhas,novo);
        }
    }
   
    free(frequencia);
    return listaFolhas;
}

NODE *criarArvore(LISTA * list){
    if(list == NULL) return NULL;
    // o i começa com cont e assim vai ficar com 2 nodes menor que a frequencia
    int i = list->tam;

    NODE *aux1,*aux2;
    ELEM *p =  list->first;
    while(i>1 || list->tam){
        NODE *new = (NODE*)calloc(1,sizeof(NODE));
        aux1 = p->no;
        p = p->prox;
        aux1 = p->no;
        new->freq = aux1->freq + aux2->freq; // soma as frenquecias
        new->esq = aux1;
        new->dir = aux2; 
        removeLista(list,0); // remove o primeiro e o segundo elemento
        removeLista(list,1);
        addLista(list,new);
      //  printf("tam, %d\n",list->tam);
        i--;
    }
    NODE *raiz = list->first->no;
    return  raiz;
}

char *trasformarTexto(Dicio*p){
    char *text = (char*)calloc(1,sizeof(char));
    int tam=0;
    int i,j;
    
    for(i=0;i<p->cont;i++){
        for(j=0;i<p->vetor[p->cont]->cap;i++){
            text[tam] = p->vetor[p->cont]->huffCode[j];
            text = (char*)realloc(text,sizeof(char)*(tam)++);
            tam++;
            
        }
    }
    return text;
}

void compactar(char* text){
    int cont;
    treeHuffamn *novo = criarHuffman(strlen(text));
    LISTA *folhas = criarfolhas(text);
    novo->raiz = criarArvore(folhas);
    PILHA *stack = criarPilha();
    Dicio *matrizPilha = criarMatrizPilha();
     DFS(novo->raiz,stack,matrizPilha);
    char *compri = trasformarTexto(matrizPilha);
    printf("%d\n",(int)strlen(compri));
   freeLista(folhas); 
}


