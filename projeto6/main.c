// igor guilherme pereira loredo nusp: 11275071 

#include <stdio.h>
#include <stdlib.h>
#include <array_list.h>
#include <string.h>


int main(){
    int chave,valor,pos1,pos2;
    char *op = (char*)malloc(10);
    array_list *list = create();
    ITEM *aux;
    
    do{
    scanf(" %s",op);
    if(strcmp(op,"add")== 0 ){
    scanf("%d %d",&chave,&valor);
    add(list,chave,valor); // ta certa
    }
    if(strcmp(op,"tamanho") == 0){
        printf("%d\n",size(list)); // ta certa
    }
    if(strcmp(op,"print") == 0){
        print(list); // ta certa
    }
    if(strcmp(op,"vazia") == 0){
        printf("%d\n",vazia(list)); // ta certa
    }
    if(strcmp(op,"indice") == 0){
        scanf("%d",&chave);
        indice(list,chave);
    }
    if(strcmp(op,"contem")== 0){
        scanf("%d",&chave);
        contem(list,chave);
    }
    if(strcmp(op,"get") == 0){
        scanf("%d",&pos1);
        aux = get(list,pos1);
        if(aux != NULL)
        printf("%d/%d\n",aux->chave,aux->valor);
    }
    if(strcmp(op,"sub")==0){
        scanf("%d %d",&pos1,&pos2);
        sub(list,pos1,pos2);
    }
    if(strcmp(op,"set")== 0){
        scanf("%d",&pos1);
        scanf("%d\n" ,&chave);
        scanf("%d\n",&valor);
        set(list,pos1,chave,valor);
    }
    if(strcmp(op,"remove") == 0){
        scanf("%d",&pos1);
        remover(list,pos1);
    }
    }while(strcmp(op,"sair") != 0);

   // free(aux);
    freArray(list);
    free(op);
    
    return 0;
}
