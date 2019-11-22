#ifndef huffman_h
#define huffman_h

// pilha
struct pilha{
    int *vet;
    int cap;
};

// estrutura para ajudar a pegar o caminho na compactção
struct Verbete{
    char valor;
    int *huffCode;
    int frequencia;
    int cap;
};
typedef struct Verbete ver;
// Dicionario de Huffman

struct Dicionario{
    ver** vetor;
    int cont;
};
typedef struct Dicionario Dicio;

// estrutura da arvore
struct node{
    char letra;
    char flag;
    int freq;
    struct node *esq, *dir;
};
struct TREE{
    struct node *raiz;
    int tam;
};

// LISTA ENCADEADA
struct elem{ // elemento
    struct node *no; // node para guardar o elemento 
    struct elem *prox; // ponteiro para o proximo elemento
};

struct list{ // descritor
    int tam;
    struct elem *first; // ponteiro para o primeiro elemento
    struct elem *last; // ponteiro para o ultimo elemento
};

typedef struct elem ELEM;
typedef struct list LISTA;

typedef struct PilhaMatriz PILHAMATRIZ;
typedef struct pilha PILHA;
typedef struct node NODE;
typedef struct TREE treeHuffamn;



//lista encadeada
LISTA *criarLista();
void addLista(LISTA *, NODE *);
void removeLista(LISTA *, int);


// instruções da arvore
treeHuffamn *criarHuffman(int);
LISTA *criarfolhas(char*);
NODE *criarArvore(LISTA*);
char *trasformarTexto(Dicio*);
void compactar(char*);
void DFS(NODE *,PILHA *,Dicio*);


#endif