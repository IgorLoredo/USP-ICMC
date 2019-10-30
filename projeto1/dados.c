#include <stdio.h>
#include <dados.h>

void inseri(dado *dados,int n){
    scanf("%d",dados->id);
    scanf("%s",dados->nome);
}
void print(dado *dados,int n){
    printf("%d\n",dados->id);
    printf("%s\n",dados->nome);
}