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
    printf("%d\n",(int)strlen(text));
    compactar(text);
    printf("%s\n",text);
    return 0;
}