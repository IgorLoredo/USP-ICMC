#include <hash.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
    char *entrada = (char*)malloc(sizeof(char)*15);
    scanf(" %s",entrada);

    free(entrada);
    return 0;
}