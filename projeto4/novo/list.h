#ifndef list
#define list
// igor guilherme pereira loredo
// 11275071
struct list_simples{
    char *nome;
    char *sobrenome;
    char *cpf;
    char *telefone;
}; // elemento da lista

// descritor da lista
struct DADOS_LIST{
    struct list_simples **primeiro; // aponta para os elementos
    int counter; // contador
};
typedef struct list_simples list_p; // struct para o cadrastro
typedef struct DADOS_LIST dados_list; // guarda os dados da lista e do no

list_p *criaCad();
dados_list *criarDados();
void cadrastro(list_p*);
void add(dados_list*,list_p*);
int busca(dados_list*,char*);
void buscaPrint(dados_list*,char*);
void remover(dados_list*,char*);
void dump(dados_list*);
void free_list(dados_list*);
#endif