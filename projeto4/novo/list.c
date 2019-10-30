#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list.h>
// igor guilherme pereira loredo
// 11275071

void cadrastro(list_p* p){
    scanf(" %s", p->nome);
    scanf(" %s", p->sobrenome); 
    scanf(" %s", p->cpf);
    scanf(" %s", p->telefone);
} // pega os dados

 list_p *criaCad(){ // retona um ponteiro do tipo list_p com os dados
    list_p *pont = (list_p*)malloc(sizeof(list_p));

    pont->nome = (char*)malloc(sizeof(char)*15);
    pont->sobrenome = (char*)malloc(sizeof(char)*15);
    pont->cpf = (char*)malloc(sizeof(char)*11);
    pont->telefone = (char*)malloc(sizeof(char)*20);

    cadrastro(pont);
    return pont; // retona
}// cria lista e manda elemento novo

dados_list *criarDados(){
    dados_list *lista= (dados_list*)calloc(1,sizeof(dados_list)); // aloca espaço de um 1 para o descritor
    lista->primeiro = (list_p**)calloc(1,sizeof(list_p*)); // criar espaço inicial de 1 para a 
    return lista; // retona descritor
} 

int busca(dados_list *lista,char *pos){ // faz a busca sequencial comparando o cpf e volta a localicao do 
    int i,s;
    for(i=0;i<lista->counter;i++){
       s = strcmp(lista->primeiro[i]->cpf,pos);
        if(s == 0){
            return i; // retona posição
        }
    }
}

void buscaPrint(dados_list*lista,char *ct){
    int pos;
    for(pos =0;pos<lista->counter;pos++){ 
        if(strncmp(ct,lista->primeiro[pos]->cpf,11) == 0){
            printf("Primeiro Nome: %s\n", lista->primeiro[pos]->nome);
            printf("Ultimo Nome: %s\n",lista->primeiro[pos]->sobrenome);
            printf("CPF: %s\n", lista->primeiro[pos]->cpf);
            printf("Telefone: %s\n", lista->primeiro[pos]->telefone);
            printf("-----------------------------\n");
            break;
        }
    }
}

void remover(dados_list *lista,char *pos){
    int i= busca(lista,pos); // manda a posição do cpf
    if(i>=0 && i<lista->counter){
    memcpy(&lista->primeiro[i],&lista->primeiro[i+1],sizeof(list_p*)*(lista->counter-i-1));
    // tranfere todo os dados para frente
    lista->primeiro = (list_p**)realloc(lista->primeiro,sizeof(list_p*)*lista->counter);
    lista->counter--; // tira um do contador
    }
}

void dump(dados_list*lista){
    int i;
    for(i=0;i<lista->counter;i++){
    printf("Primeiro Nome: %s\n", lista->primeiro[i]->nome);
    printf("Ultimo Nome: %s\n",lista->primeiro[i]->sobrenome);
    printf("CPF: %s\n", lista->primeiro[i]->cpf);
    printf("Telefone: %s\n", lista->primeiro[i]->telefone);
    printf("-----------------------------\n");
    }
} // printa todos os elementos inseridos, ele usa a quantidade que tem no descritor para printar


void add(dados_list *lista,list_p *new){
    if(lista == NULL){printf("erro\n");} // ver e existe lista
    lista->primeiro= (list_p**)realloc(lista->primeiro,sizeof(list_p*)*lista->counter+1); // realoca espaço
    lista->primeiro[lista->counter] = new; // adiciona o novo elemento na matriz
    lista->counter++; // aumenta o contador
}

// desalocar espaco
void free_list(dados_list*p){
    int i;
    for(i=0;i<p->counter;i++)
        free(p->primeiro[i]);
}   

