#include <stdlib.h>
#include <dyn_list_simple.h>

DYN_LIST_SIMPLE *dyn_list_simple_create(int (*cmp)(void *, void *)) {
	DYN_LIST_SIMPLE *list; // 8 bytes na Stack

	// ao menos 28 bytes na heap
	list = (DYN_LIST_SIMPLE *) calloc(1, sizeof(DYN_LIST_SIMPLE));
	list->cmp = cmp;

	// Registrador (memória dentro da CPU) 8 bytes
	return list;
}


/*
 
   --------- 
   |       |    0x0000 descritor comeca aqui
   |       |
   |       |
   |       |
   | first |			**p = &first
   |       |			*p = first
   |       |
   |       |
   ---------
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
   |       |
 

 
   8 + 8 + 4 + 8 bytes = 28 bytes
  --------------------------------
  | DYN_LIST_SIMPLE_ELEM *first  |---|
  | DYN_LIST_SIMPLE_ELEM *last   |---|
  | counter                      | = 0
  | cmp                          | 
  --------------------------------

  	new
  	|
	v
  	--------
	| elem |---> o
	| next |
  	--------

 */

int dyn_list_simple_add(DYN_LIST_SIMPLE *list, int pos, void *elem) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos > list->counter) return INVALID_POS;

	DYN_LIST_SIMPLE_ELEM **p;
	int ct = 0;

	// Criando novo elemento
	DYN_LIST_SIMPLE_ELEM *new;
	new = (DYN_LIST_SIMPLE_ELEM *) 
		malloc(sizeof(DYN_LIST_SIMPLE_ELEM));
	new->elem = elem;

	// Procurar o local de insercao
	p = &list->first;
	while (ct++ < pos && (p = &((*p)->next)));

	// Fazendo a insercao
	new->next = *p;
	*p = new;

	// Alterando last
	if (pos == list->counter) list->last = new;

	// Incrementando o contador
	list->counter++;

	return SUCCESS;
} 

int dyn_list_simple_add_first(DYN_LIST_SIMPLE *list, void *elem) {
	return dyn_list_simple_add(list, 0, elem);
}

int dyn_list_simple_add_last(DYN_LIST_SIMPLE *list, void *elem) {
	if (!list) return INVALID_LIST;
	return dyn_list_simple_add(list, list->counter, elem);
}

void *dyn_list_simple_get(DYN_LIST_SIMPLE *list, int pos, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return NULL;
	}
	if (pos < 0 || pos >= list->counter) {
		*error = INVALID_POS;
		return NULL;
	}

	// first					last 
	//   |						  |
	//   v						  v
	//   0        1        2        3        4        5
	// ------   ------   ------   ------   ------   ------   
	// |    |   |    |   |    |   |    |   |    |   |    |
	// |    |-->|    |-->|    |-->|    |-->|    |-->|    |--|
	// ------   ------   ------   ------   ------   ------
	
	DYN_LIST_SIMPLE_ELEM *aux = list->first;
	while (pos-- && (aux = aux->next));
	return aux->elem;
}

int dyn_list_simple_free(DYN_LIST_SIMPLE *list) {
	if (!list) return INVALID_LIST;

	DYN_LIST_SIMPLE_ELEM *p, *aux;
	p = list->first;

	while (p) {
		aux = p->next;
		free(p);
		p = aux;
	}
	free(list);

	return SUCCESS;
}

int dyn_list_simple_remove(DYN_LIST_SIMPLE *list, int pos) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos >= list->counter)
		return INVALID_POS;

	DYN_LIST_SIMPLE_ELEM *p, *prev;
	int counter = 0;

	prev = NULL;
	p = list->first;
	while (counter < pos) {
		prev = p;
		p = p->next;
		counter++;
	}
	if (prev) {
		prev->next = p->next;
		if (list->last == p) list->last = prev;
	} else list->first = p->next;
	free(p);
	list->counter--;

	/*
	p = list->first;
	while (counter++ < pos-1) p = p->next;
	if (pos == 0) {
		list->first = p->next;
		free(p);
	} else {
		aux = p->next;
		p->next = aux->next;
		free(aux);
		if (pos == list->counter-1) {
			list->last = p;
		}
	}
	list->counter--;*/

	return SUCCESS;
}

int dyn_list_simple_sequential_search(DYN_LIST_SIMPLE *list, 
			void *elem, int *error) {

	if (!list) {
		*error = INVALID_LIST;
		return -1;
	}

	DYN_LIST_SIMPLE_ELEM *p;
	int i = 0;

	p = list->first;
	while (p && list->cmp(p->elem, elem) && (p = p->next)) {
		i++;
	}
	if (p) {
		*error = SUCCESS;
		return i;
	} else {
		*error = INVALID_POS;
		return -1;
	}
}

int dyn_list_simple_size(DYN_LIST_SIMPLE *list) {
	if (!list) return INVALID_LIST;
	return list->counter;
}


