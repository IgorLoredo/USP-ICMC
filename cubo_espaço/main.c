#include <stdio.h>
#include <stdlib.h>
#include <cube.h>
#include <string.h>

int main(){
    long double x,y,z;
    long double cont;
    char *com = (char*)malloc(10*sizeof(char));

    scanf("%Le %Le %Le",&x,&y,&z); // pega as dimensões só para limpar o teclado mais nao usa 
    CUBE_SPARSE *new = create_cube(HASH_PRIME,HASH_PRIME,HASH_PRIME,0); // aloca o espaço usando o primo defindo

    while(!feof(stdin)){
        scanf("%s",com);
        if(strcmp(com,"put") == 0){
            scanf("%Le %Le %Le %Lf",&x,&y,&z,&cont); // pega como long double mas como divide pelo primo vira um long int
            cube_add(new,(long int)x%HASH_PRIME,(long int)y%HASH_PRIME,(long int)z%HASH_PRIME,cont); // pega o resto da divisão
        }else if(strcmp(com,"get") == 0){
            scanf("%Le %Le %Le ",&x,&y,&z);
           printf("%Lf\n",cube_get(new,(long int)x%HASH_PRIME,(long int)y%HASH_PRIME,(long int)z%HASH_PRIME));
        }else if(strcmp(com,"remove") == 0){
            scanf("%Le %Le %Le",&x,&y,&z);
          cube_remove(new,(long int)x%HASH_PRIME,(long int)y%HASH_PRIME,(long int)z%HASH_PRIME);
        }
    }

    free(new); // free no cubo
    free(com);
    return 0;
}