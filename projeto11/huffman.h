#ifndef huffman_h
#define huffman_h

// pilha
struct pilha{
    int *vet;
    int cap;
};
typedef struct pilha PILHA;

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
typedef struct node NODE;
typedef struct TREE treeHuffamn;


// instruções da arvore
treeHuffamn *criarHuffman(int);
NODE **criarfolhas(char*, int*);
NODE *criarArvore(NODE**,int);

//TABELAHUFFMAN *criarTabelaHuffman();
//compactarHuffman(text,&tabela);
//descompactarHuffman(textCompac,tabela);
//liberarTabelaHuffman(&tabela);

#endif