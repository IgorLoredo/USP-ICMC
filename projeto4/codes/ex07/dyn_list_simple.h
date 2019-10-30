#ifndef _DYN_LIST_SIMPLE_
#define _DYN_LIST_SIMPLE_

/*
 	Lista simplesmete encadeada
 	---------      ---------      ----------
	| int   |      | int   |      | int    |
	|       |      |       |      |        |
	| next  |--->  |next   | ---> | next   |--
 	---------      ---------      ---------- |
						---
 	Lista duplamente encadeada
 	---------      ---------      ----------
	| int   |      | int   |      | int    |
      --| prev  | <--- | prev  | <--- | prev   |
      |	| next  |--->  |next   | ---> | next   |--
 	---------      ---------      ---------- |
*/

/*
 	-------
 	|     | uc, c 	| i	|d, vp
 	|     |		|       |
 	|     |		|       |
 	|     |		|       |
 	|     |                 |
 	|     |                 |
 	|     |                 |
 	|     |                 |
 	-------
 */

#define SUCCESS 	0
#define INVALID_LIST 	-1
#define REMOVE_ERROR 	-2
#define GET_ERROR 	-3
#define INVALID_POS 	-4

// Elemento da lista
struct dyn_list_simple_elem {
	void *elem;
	struct dyn_list_simple_elem* next;
};
typedef struct dyn_list_simple_elem DYN_LIST_SIMPLE_ELEM;

// Descritor da lista
struct dyn_list_simple {
	DYN_LIST_SIMPLE_ELEM *first;
	DYN_LIST_SIMPLE_ELEM *last;
	int (*cmp)(void *, void *);
	int counter;
};
typedef struct dyn_list_simple DYN_LIST_SIMPLE;

// Funcoes
DYN_LIST_SIMPLE *dyn_list_simple_create(int (*)(void *, void *));
int dyn_list_simple_add(DYN_LIST_SIMPLE *, int, void *);
int dyn_list_simple_add_first(DYN_LIST_SIMPLE *, void *);
int dyn_list_simple_add_last(DYN_LIST_SIMPLE *, void *);
void *dyn_list_simple_get(DYN_LIST_SIMPLE *, int, int *);
int dyn_list_simple_free(DYN_LIST_SIMPLE *);
int dyn_list_simple_remove(DYN_LIST_SIMPLE *, int);
int dyn_list_simple_sequential_search(DYN_LIST_SIMPLE *, void *, int *);
int dyn_list_simple_size(DYN_LIST_SIMPLE *);

//dyn_list_simple_binary_search()
//dyn_list_simple_sort()
//dyn_list_simple_reverse()
//dyn_list_simple_copy()

#endif
