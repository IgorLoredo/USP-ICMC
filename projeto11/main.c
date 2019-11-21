#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>


int main(){
    int i;
    char *text = (char*)malloc(sizeof(char));

    for(i=0;(text[i] = getchar()) != '\n';++i)
        text = (char*)realloc(text,sizeof(char)*(i+2));
    
    text[i] = '\0';
    treeHuffamn *novo = criarHuffman(strlen(text));
    printf("tamanho da palavra %d\n",i);
    int cont;
    NODE **folhas = criarfolhas(text,&cont);
    novo->raiz = criarArvore(folhas,cont);
    return 0;
}