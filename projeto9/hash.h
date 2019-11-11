#ifndef _hash_h
#define _hash_h

#include <stdio.h> // para funiona o FILE

#define SUCESSO 1
#define ERRO_ARQ  -1
#define ERRO_HASH -2
#define ERRO_VET -3

#define PRIMO 9230051 // primo para divição
               
struct elem{
    unsigned long int quant;
    char **palavra;
};

struct hash{
    unsigned long int primo;
    unsigned long int maior;
    struct elem **table;
};

typedef struct elem hashElem;
typedef struct hash HASH;

// deixei alguns cabeçalhos encapsulados

hashElem *criarElem(); // cria elementos
HASH *criarHash(unsigned long int); // cria tabela
unsigned long int gerarHash(char*); // gerar hash 

int processar(FILE*,HASH*); // procesar e mostra o angrama
int freeTudo(HASH *); // dar free
#endif
