#ifndef _dyn_list_	// diretiva de compilacao
#define _dyn_list_	// diretiva de compilacao

/*
 	dyn_list

	|
	v
	---------------------------------
	|	|	|	|	|   
	|    |  |       |       |       |
	-----|---------------------------
	     v
	     struct, int
 */

// defines/macros
#define SUCCESS		0
#define INVALID_LIST 	-1
#define REMOVE_ERROR 	-2
#define GET_ERROR 	-3
#define INVALID_POS	-4

struct dyn_list_elem {
	void *elem;	// 8 bytes
};
typedef struct dyn_list_elem DYN_LIST_ELEM;

struct dyn_list {
	DYN_LIST_ELEM *first;
	int (*cmp)(void *, void *);
	int counter;
};
typedef struct dyn_list DYN_LIST;

// Headers

// criar a lista
DYN_LIST *dyn_list_create(int (*)(void *, void *));
// adicionar elementos a lista
int dyn_list_add(DYN_LIST *, void *);
// remover elementos da lista
int dyn_list_remove(DYN_LIST *, int);
// retornar um elemento da lista
DYN_LIST_ELEM *dyn_list_get(DYN_LIST *, int, int *);
// ordenacao
int dyn_list_sort(DYN_LIST *);
// busca por um elemento
int dyn_list_sequential_search(DYN_LIST *, void *, int *);
int dyn_list_binary_search(DYN_LIST *, void *);
// copiar a lista
DYN_LIST *dyn_list_copy(DYN_LIST *, int *);
// reverter uma lista
int dyn_list_reverse(DYN_LIST *);
// insercao em qualquer posicao da lista
int dyn_list_insert(DYN_LIST *, int, void *);
// tamanho da lista
int dyn_list_size(DYN_LIST *);
// libera a lista
void dyn_list_free(DYN_LIST *);

#endif
