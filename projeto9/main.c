#include <hash.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
    HASH *new =  criarHash(PRIMO);
    char *entrada = (char*)malloc(sizeof(char)*15);
    scanf("%s",entrada);
    FILE *arquivo = fopen(entrada,"r");
    processar(arquivo,new);
    freeTudo(new);
    free(entrada);
    fclose(arquivo);
    return 0;
}