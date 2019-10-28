// igor guilherme pereira loredo nusp: 11275071 

#ifndef array_list_h
#define array_list_h


#define SUCCESS     0
#define erro    -1
#define erro_no     -2
#define erro_remove -3


struct item{
    int chave;
    int valor;
};
typedef struct item ITEM; // item

struct NO{
    ITEM **itens;
    int tamanho;
    int ultimo; 
    struct NO *next; // nó
};
typedef struct NO no;

struct ARRAY_LIST{
    no *fist;
    no *last;
    int nElementos;
};

typedef struct ARRAY_LIST array_list;



array_list *create(); // cria o array list
ITEM *create_item(int,int); // cria uma item simples
no *create_no(int); // cria um nó 
no *busca_add(array_list*,int,int*); // busca o lugar para add
no *busca_remover(array_list*,int ,int*); // busca para remover
ITEM *get(array_list*,int); 

int add(array_list*,int,int); // adicionar itens
int remover(array_list*,int); // remove o elemento
int tamanho(array_list*); // mostra o tamanho da arraylist
int vazia(array_list *); // mostra se a lista tem elementos
int size(array_list*); // mostra o tamanho da lista
int busca_binaria(ITEM **, int, int); // busca binaria dos elementos


void set(array_list *,int,int,int); // muda chave e valor na posição dada
void freArray(array_list*); // dar free em toda array e  itens
void indice(array_list*,int); // mostra 
void contem(array_list*,int); // mostra se tem o elemento no array list
void print(array_list*); // print o elementos do array list
void sub(array_list*,int,int);

#endif
  