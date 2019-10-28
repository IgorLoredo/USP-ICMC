// igor guilherme pereira loredo nusp: 11275071 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <array_list.h>

array_list *create(){
    array_list *new = (array_list*)calloc(1,sizeof(array_list));
   // list->fist->next= list->last;
    return new;
} // cria uma array

ITEM *create_item(int chave,int valor){
    ITEM *new = (ITEM *)malloc(sizeof(ITEM));
    new->chave = chave;
    new->valor = valor;
    return new;
} // cria um item e retona ele

no *create_no(int tam){
    no *no_array = (no*)calloc(1,sizeof(no));
    no_array->tamanho = tam;
    no_array->itens = (ITEM**)calloc(tam,sizeof(ITEM*));
    return no_array;
} // recebe um tamanho e fazer um nó

int busca_binaria(ITEM **vetor, int chave, int tam) { // busca binaria dos elesmentos
    int inicio = 0;
    int fim = tam - 1;
    int meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (vetor[meio]->chave == chave) {
            return meio; // se o elemento estar no lugar
        } else if (vetor[meio]->chave < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return erro; // retona negativo 
} 

no *busca_add(array_list* list,int chave ,int* pos){
    no *p = list->fist; 
    int i;
    while(p && (p->ultimo == p->tamanho)){ //caso o p seja null ou se p não tiver totalmente preenchido
       i = busca_binaria(p->itens,chave, p->ultimo); // busca binaria da posição da chave
        if(i>=0){
            *pos =i; // pega a posição
            return p; // retona o nó que estar o elemento
        }
        p = p->next; // para o proximo nó
    }
    *pos = erro_no; // retorna erro como posição e indica n há chaves
    return list->last; // retona o ultimo nó
}

int add(array_list *list,int chave, int valor){
    if(!list){return erro;} // caso a lista não exista

    ITEM *new_item = create_item(chave,valor); // cria um elemento nó
    if(list->nElementos == 0){ // caso a arraylist não tive nada de elementos no last ou fist
        no *new =create_no(10);
        new->itens[0] =new_item;
        new->ultimo++;
        list->fist = list->last = new; // faz last apontar para new
        list->nElementos++;
        return SUCCESS;
    }
 
    int pos_no; // posição para ser inserida
    no *no_recebe = busca_add(list,chave,&pos_no); // recebe o nó para ser inserido

    if(pos_no == -2){ // caso elemntos pode ser inserido na ultima posição
       if(list->last->ultimo == list->last->tamanho){ // o nó estava cheio
        no *new_no = create_no(list->last->tamanho*2);
        new_no->itens[new_no->ultimo] = new_item;
        new_no->ultimo++;
        list->last->next = new_no;
        list->last = new_no; // new_nó passa a ser last
        list->nElementos++;
        return SUCCESS;
       }else{
           list->last->itens[list->last->ultimo++] = new_item;
           list->nElementos++;
            return SUCCESS; 
       }

    }else{
        ITEM *aux = no_recebe->itens[pos_no]; 
        no_recebe->itens[pos_no] = new_item;
        add(list,aux->chave,aux->valor); 
        return SUCCESS;
    }
    return erro;
}

void indice(array_list* list,int chave){
    int i;
    int flag=-1,cont =0;
    no *p = list->fist;
    while(p){ //
        i =0; // contador para as chaves 
        while(i<p->ultimo && ++cont){
            //cont++;
            if(chave == p->itens[i]->chave){
            flag = cont; 
            break; // caso ache a chave  
            }else{
                i++;
            }
        }
        p = p->next;
    }
    if(flag != -1) // caso há o elemento no array 
        printf("%d\n",flag-1);
    free(p);
}

void contem(array_list* list,int chave){ // passa pelos itens vendo se a chave estar contigo neles
    int flag=0;
    no *p = list->fist;
    while(p){      
        if(busca_binaria(p->itens,chave,p->ultimo)>=0 ){ // usa busca binaria
        flag =1; // se há chaves iguais 
        break;
        }
       p = p->next;
    }
    p = NULL;
    printf("%d\n",flag);
    free(p);
}

void freArray(array_list* list){
    int i;
    no *p = list->fist;
    no *aux; // auxiliar para guardar um endereço 
    while(p){
        aux=p->next;
        for(i=0;i<p->ultimo;i++)
            free(p->itens[i]); // dar free nos itens de cada nó
        free(p); // dar free na lista toda
        p=aux; // pega o endereço do proximo nó
    }

}

ITEM *get(array_list *list, int pos){
    if(!list){return NULL;} // caso a lista não exista
    if(pos<0 || pos>list->nElementos){return NULL;} // caso uma posição invalida
    if(pos<10){return list->fist->itens[pos];} // caso o pos estiver no primeiro nó
    int i=0,cont=0;
    no *p = list->fist; // pega o endereço de fist
    while(p){
        i=0;
        while((i <p->ultimo)){
        i++; 
            if(cont++ == pos){
                return p->itens[i-1];
            }
       }
       p = p->next;
    }     
    return NULL;
}

void sub(array_list*list,int pos1,int pos2){
    array_list *new= create(); // cria uma lista nova
    ITEM *aux;
    int i;
   // int tam = pos2 - pos1;
    for(i=pos1;i<pos2;i++){
        aux =  get(list,i); // pega um elemento 
        add(new,aux->chave,aux->valor); // adiciona na nova lista
    }
    print(new); 
    freArray(new); // dar frre na nova lista
}

no *busca_remover(array_list* list,int pos ,int*pos_no){ // buscar posição para ser removida
    int i=0,cont=0;
    no *p = list->fist; // pega o endereço de fist
    while(p){
        i=0;
        while((i <p->ultimo)){
        i++; 
            if(cont++ == pos){
                *pos_no= i-1; ;// posição para ser removida
                return p; // envia o nó para ser removido
            }
       }
       p = p->next;
    }    
    *pos_no = erro_no;
    return NULL;
}

int remover(array_list* list,int pos){
    if(pos<0 || pos > list->nElementos){return erro_remove;}
    int i;
    int pos_no; // posição para ser removida
    no *p = busca_remover(list,pos,&pos_no);
    if(p->ultimo < p->tamanho){

        for(i = pos_no;i<p->ultimo-1;i++)
                p->itens[i]= p->itens[i+1];  // passa os valores da frente para uma posição atras

       free(p->itens[p->ultimo]); //dar free no ultimo elemento
        p->ultimo--;
        list->nElementos--;
        if(p->ultimo == 0) // caso for o ultimo elemnto do nó, dá free no nó
            free(p);
            return SUCCESS; // retona sucesso
    }else{

        if(p->next == NULL){ // caso seja o ultimo nó da arraylist
            for(i = pos_no;i<p->ultimo-1;i++)
                p->itens[i]= p->itens[i+1]; // passa os valores da frente para uma pos_noição atras

           free(p->itens[p->ultimo]);
            p->ultimo--;
            list->nElementos--;
            return SUCCESS;
        }else{
       
            for(i = pos_no;i<p->ultimo-1;i++)
                p->itens[i]= p->itens[i+1]; // passa os valores da frente para uma posição atras


            list->nElementos--;
            return SUCCESS;
           
        }

    }
    return erro_remove;
}

void set(array_list *list,int pos ,int chave,int valor){
    remover(list,pos);
    add(list,chave,valor);
    
}


void print(array_list*list){ // printa a arraylist
    int i;
    no *p= list->fist;
    int cont=0;
    while(p){
        for(i=0;i<p->ultimo;i++){ // mostra todos os elementos pelo nó
            printf("%d: ",cont++);
            printf("%d/%d\n", p->itens[i]->chave,p->itens[i]->valor);
        }
        printf("\n\n");
        p = p->next; // passa para o proximo
    }
} // print dos elementos 


int size(array_list* list){
    if(!list){
         return erro;
    }
    return list->nElementos; // retona numero de elementos na lista
}

int vazia(array_list *list){
    if(size(list) == 0){ // se a lista tiver zera retona 1
        return 1; 
    }else{
        return 0; // se a lista tiver vazia
    }
}