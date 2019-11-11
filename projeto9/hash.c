//#include <hash.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

//aloca ponteiro para habe
HASH *criarHash(unsigned long int tam){
    HASH *p = (HASH*)calloc(1,sizeof(HASH));
    p->primo = tam;
    p->table = (hashElem**)calloc(tam,sizeof(hashElem*));
    return p;
}

unsigned long int gerarHash(char*palavra){
    unsigned long int hash=1,i;
    unsigned long int aux;
    int *vetPri = (int*)malloc(27*sizeof(int));
    // vet com os primos pequenos
    vetPri[0] = 2;
    vetPri[1] = 3; 
    vetPri[2] = 5;
    vetPri[3] =7; 
    vetPri[4] =11; 
    vetPri[5] =13; 
    vetPri[6] =17; 
    vetPri[7] =19; 
    vetPri[8] =23; 
    vetPri[9] =29; 
    vetPri[10] =31; 
    vetPri[11] =37; 
    vetPri[12] =41; 
    vetPri[13] =43; 
    vetPri[14]= 47;
    vetPri[15]= 53;
    vetPri[16] =59;
    vetPri[17] =61;
    vetPri[18] =67;
    vetPri[19] =71;
    vetPri[20] =73; 
    vetPri[21] =79; 
    vetPri[22] =83; 
    vetPri[23] =89; 
    vetPri[24] =97; 
    vetPri[25] =101; 
 // multipçlicar as letras por primos pequenos e depois divide por um primo grande

    for(i=0;i<strlen(palavra);i++){
        aux = vetPri[(palavra[i]-97)];
        hash = (hash *aux) % PRIMO;
    }
    return hash;
}

hashElem *criarElem(){
    hashElem* new = (hashElem*)calloc(1,sizeof(hashElem));
	new->quant=0;
    new->palavra = (char**)calloc(1,sizeof(char*));
    return new;
} // cria elemento de hash

int acharPosi(HASH* table, unsigned long int id, char*palavra){
    if(!table) return ERRO_HASH;
    if(!table->table[id]){ // caso n exista o elemento
        hashElem *new = criarElem();
        new->palavra[new->quant] = palavra;
		new->quant++;
        table->table[id] = new;        
    }
    else{ // caso exista ele é um anagrama
        hashElem *p = table->table[id];
        p->palavra = (char**)realloc(p->palavra,sizeof(char*)*p->quant+1);
    	p->palavra[p->quant] = palavra;
		p->quant++;

    }

    if(table->maior < table->table[id]->quant ){
	    table->maior = table->table[id]->quant;
	} // maior anarama
		
    return SUCESSO;
}

int vetHash(HASH *p,hashElem **vet){
	if(!p) return ERRO_HASH;
	int num=0;
	unsigned long int i;
	for(i=0;i<p->primo;i++){
		if(p->table[i]){
			if(p->table[i]->quant == p->maior){
				vet = (hashElem**)realloc(vet,sizeof(hashElem*)*num+1);
				vet[num] = p->table[i];
				num++;
			}
		}
	}
	return num;
} // criar vetor que guarda os anagramsa

int organizar(int num,hashElem **vet){
    int i,j;
    hashElem *aux = criarElem();
    for(i=0;i<num-1;i++){
        for(j=0;j<num-i;j++){
            if(strcmp(vet[i]->palavra[0],vet[i+1]->palavra[0]) >= 0){
                aux =vet[i+1];
                vet[i+1] = vet[i];
                vet[i] = aux; 
            }
        }
    }

}
int printElem(hashElem* elem){
    if(!elem) return ERRO_HASH;
    int i;

    for(i=0;i<elem->quant-1;i++)
        printf("%s, ",elem->palavra[i]);
	printf("%s",elem->palavra[i]);
    printf("\n");
	return SUCESSO;
} // print um elemento sozinho

int printAnagrama(int num,hashElem **vet){
	if(!vet) return ERRO_VET;
	int i;
	for(i=0;i<num;i++)
		printElem(vet[i]);
	return SUCESSO;
} // printa o anagrama

int processar(FILE* arq,HASH *table){
    if(!arq) return ERRO_ARQ;
    unsigned long int id=0;
    unsigned long int i=0;
    char **aux = (char**)malloc(sizeof(char*));
    aux[i] = (char*)calloc(20,sizeof(char));

    do{
        id = gerarHash(aux[i]);
       	acharPosi(table,id,aux[i]);
         i++;
        aux = (char**)realloc(aux,sizeof(char*)*i+2);
        aux[i] = (char*)calloc(20,sizeof(char));
    } while(fscanf(arq," %s",aux[i]) != EOF);

	hashElem **vetResposta = (hashElem**)malloc(sizeof(hashElem*));

	int numAnagrama = vetHash(table,vetResposta);
    organizar(numAnagrama,vetResposta);
	printf("%d\n",numAnagrama);
	printAnagrama(numAnagrama,vetResposta);    
    return SUCESSO;
} // processar e uni todas a funções


int freeElem(hashElem*vet){
    unsigned long int i;
    for(i=0;i<vet->quant;i++)
        free(vet->palavra[i]);

    free(vet->palavra);
    free(vet);
    return SUCESSO;
} // dar free no elemento/ anagrama

int freeTudo(HASH *table){
    if(!table) return ERRO_HASH;
    unsigned long int i=0;
    for(i=0;i<table->primo;i++){
        if(table->table[i]){
             freeElem(table->table[i]);
        }
    }
    free(table->table);
    free(table);
    return SUCESSO;
} // dar em toda hash e no anagrama