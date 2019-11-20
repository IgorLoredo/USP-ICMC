#ifndef huffman_h
#define huffman_h

typedef unsigned char byte; // vai de 0 a 255

struct node{
    char letra;
    int freq;
    struct node *esq, *dir;
};
struct TREE{
    struct node *raiz;
    int tam;
};
typedef struct node NODE;
typedef struct TREE treeHuffamn;

treeHuffamn *criarHuffman(int);
//int criarAvore();
NODE **criarfolhas(char *, int *);
//TABELAHUFFMAN *criarTabelaHuffman();
//compactarHuffman(text,&tabela);
//descompactarHuffman(textCompac,tabela);
//liberarTabelaHuffman(&tabela);

#endif