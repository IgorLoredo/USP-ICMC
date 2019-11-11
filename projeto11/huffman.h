#ifndef huffman_h
#define huffman_h

typedef unsigned char byte; // vai de 0 a 255

struct node{
    int valor;
    byte codigo;
    struct node *esq *dir;
};

typedef struct node NODE;


#endif