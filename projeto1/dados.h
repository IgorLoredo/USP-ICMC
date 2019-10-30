#ifndef dados
#define dados

struct est{
    char nome;
    int id;
};
typedef struct est dado;

void inseri(dado *dados,int n);
void print(dado *dados,int n);
   

#endif
