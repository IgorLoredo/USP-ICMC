#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list.h>
// igor guilherme pereira loredo
// 11275071

int main(int argc, int *argv[]){
    char *op,*ctf; // cria vetores de entrada
    op = (char*)malloc(sizeof(char)*10);
    ctf =(char*)malloc(sizeof(char)*11);
    list_p *lista; // cria elemento para receber os dados 
    dados_list *Dados_lista = criarDados(); // cria descritor

   do{
    scanf("%s",op);
    if(strcmp(op,"cadastrar") == 0){
        lista = criaCad(); // recebe o dados
       add(Dados_lista,lista); // adiciona ao descritor
    }else if(strcmp(op,"buscar") == 0){
        scanf(" %s",ctf); // pega o cpf para printar
        buscaPrint(Dados_lista,ctf); // printa o cpf
    }else if(strcmp(op,"dump") == 0){
        dump(Dados_lista); // print todos os elementos
    }else if(strcmp(op,"remover") == 0){
        scanf(" %s",ctf); // pego o cpf para remover 
        remover(Dados_lista,ctf);// remove o elemento
    }
    
    } while(strcmp(op,"sair") != 0);

    
    // libera a memroria
    free(lista);
    free_list(Dados_lista);
    free(Dados_lista);
    free(op);
    free(ctf);
    return 0;
} 
