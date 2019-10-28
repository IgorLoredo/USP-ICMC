// igor guilherme pereira loreod nusp: 11275071
#include <stdlib.h>
#include <stdio.h>
#include <tdf.h>
#include <math.h>

int main(){
    FILE *arquivo;
    int tam_vet,C;
    char *op = (char*)malloc(sizeof(char)*10);
    scanf(" %s",op);
    scanf("%d",&C);
    arquivo = fopen(op,"rb");
    if(arquivo == NULL) { printf("\nerro no arquivo\n");}  
   
    unsigned char *audio = abrir(arquivo,&tam_vet);
    printf("%d\n",tam_vet);   
    clear_audio(audio,tam_vet,C);

    
    free(audio);
    free(op);
    fclose(arquivo);
    return 0;
}