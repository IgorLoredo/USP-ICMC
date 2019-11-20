#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>


int main(){
    int i;
    char *text = (char*)malloc(sizeof(char));

    for(i=0;(text[i] = getchar()) != '\n';++i)
        text = (char*)realloc(text,sizeof(char)*i+2);
    
    text[i] = '\0';
    printf("%d",i);
    
    int *cont;
    NODE **new = criarfolhas(text,cont);
    treeHuffamn *novo = criarHuffman(strlen(text));
    return 0;
}