#include <dyn_list_double.h>

DYN_LIST_DOUBLE *dyn_list_double_create(int (*cmp)(void *, void *)) {
	/*
		-----------------
	 	|first	   NULL	|
	 	|last      NULL |
	 	|cmp       0xAB |
	 	|counter     0  |
		-----------------
	 */
	DYN_LIST_DOUBLE *list; // 8 bytes (Stack)
	list = (DYN_LIST_DOUBLE *) 
		calloc(1, sizeof(DYN_LIST_DOUBLE)); // 28 bytes (Heap)
	list->cmp = cmp;
	return list;
}

int dyn_list_double_add(DYN_LIST_DOUBLE *list, int pos, void *elem) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos > list->counter) return INVALID_POS;

	/*
	 	DYN_LIST_DOUBLE
		-----------------
	 	|first	   	|-----
	 	|last           |--  |
	 	|cmp       0xAB | |  |
	 	|counter     1  | |  |
		----------------- |  |
				  v  v
		DYN_LIST_DOUBLE_ELEM
		---------
		| void *|
		| prev  |--|
		| next  |--|
		---------
	 */
	DYN_LIST_DOUBLE_ELEM *new; // Stack (8 bytes)
	new = (DYN_LIST_DOUBLE_ELEM *) // região alocada na heap
		calloc(1, sizeof(DYN_LIST_DOUBLE_ELEM));
	new->elem = elem;

	// percorrer até a  posição pos
	int counter = 0; // Stack (4 bytes)
	DYN_LIST_DOUBLE_ELEM **p = &list->first;
	while (counter++ < pos && (p = &(*p)->next));

	// SOLUCAO 3
	if (*p) {
		new->prev = (*p)->prev;
		new->next = *p;
		(*p)->prev = new;
		*p = new;
	} else {
		*p = new;
		new->prev = list->last;
		list->last = new;
	}

	list->counter++;

	return SUCCESS;

	/* SOLUCAO 2
	// Inserção
	if (p) {
		if (p->prev) p->prev->next = new;
		new->prev = p->prev;
		new->next = p;
		p->prev = new; 
		if (!pos) list->first = new;
	} else {
		new->prev = list->last;
		new->next = NULL;
		if (list->last) {
			list->last->next = new;
			list->last = new;
		} else {
			list->first = new;
			list->last = new;
		}
	}*/

	/* SOLUCAO 1
	if (!list->counter) {
		list->first = list->last = new;
	} else if (pos == 0) {
		new->next = p;
		p->prev = list->first = new;
	} else if (pos == list->counter) {
		new->prev = p;
		p->next = list->last = new;
	} else {
		new->prev = p->prev;
		p->prev->next = new;
		new->next = p;
		p->prev = new;
	}
	list->counter++;*/
}

int dyn_list_double_add_first(DYN_LIST_DOUBLE *list, void *elem) {
	return dyn_list_double_add(list, 0, elem);
}

int dyn_list_double_add_last(DYN_LIST_DOUBLE *list, void *elem) {
	if (!list) return INVALID_LIST;
	return dyn_list_double_add(list, list->counter, elem);
}

void *dyn_list_double_get(DYN_LIST_DOUBLE *list, 
				int pos, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return NULL;
	}

	if (pos < 0 || pos >= list->counter) {
		*error = INVALID_POS;
		return NULL;
	}

	int counter = 0;
	DYN_LIST_DOUBLE_ELEM *p = list->first;
	while (counter++ < pos && (p = p->next));

	*error = SUCCESS;

	return p->elem;
}

/*
void clean(DYN_LIST_DOUBLE_ELEM *p) {
	if (p->next)
		clean(p->next);
	free(p);
}*/

int dyn_list_double_free(DYN_LIST_DOUBLE *list) {
	if (!list) return INVALID_LIST;

	// Outra solucao 3: iterativa da 2
	
	/* Solucao 2
	DYN_LIST_DOUBLE_ELEM *p = list->first;
	clean(p);*/

	// Solucao 1
	DYN_LIST_DOUBLE_ELEM *p = list->first;
	while (p->next != NULL) {
		p = p->next;
		free(p->prev);
	}
	free(p);
	free(list);

	return SUCCESS;
}

int dyn_list_double_remove(DYN_LIST_DOUBLE *list, int pos) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos >= list->counter) return INVALID_POS;

	DYN_LIST_DOUBLE_ELEM *p = list->first;
	int counter = 0;
	while (counter++ < pos && (p = p->next));
	
	if (p->prev)
		p->prev->next = p->next;
	else
		list->first = p->next;

	if (p->next)
		p->next->prev = p->prev;
	else
		list->last = p->prev;
	free(p);
	list->counter--;

	return SUCCESS;
}

int dyn_list_double_sequential_search(
		DYN_LIST_DOUBLE *list, void *elem, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return -1;
	}

	int i;
	DYN_LIST_DOUBLE_ELEM *p = list->first;
	for (i = 0; i < list->counter; i++) {
		if (!list->cmp(p->elem, elem)) {
			*error = SUCCESS;
			return i;
		}
		p = p->next;
	}
	*error = ELEM_NOT_FOUND;
	return -1;
}

int dyn_list_double_size(DYN_LIST_DOUBLE *list) {
	if (!list) return INVALID_LIST;
	return list->counter;
}

//dyn_list_double_binary_search()
//dyn_list_double_reverse()

int dyn_list_double_sort(DYN_LIST_DOUBLE *list) {
	if (!list) return INVALID_LIST;

	void *aux;
	int i, j, error;
	for (i = 0; i < list->counter; i++) {
		DYN_LIST_DOUBLE_ELEM *e0 =
			dyn_list_double_get(list, i, &error);
		for (j = i+1; j < list->counter; j++) {
			DYN_LIST_DOUBLE_ELEM *e1 =
			   dyn_list_double_get(list, j, &error);
			if (list->cmp(e1->elem, e0->elem) < 0) {
				aux = e0->elem;
				e0->elem = e1->elem;
				e1->elem = aux;
			}
		}
	}

	return SUCCESS;
}

DYN_LIST_DOUBLE *dyn_list_double_copy(DYN_LIST_DOUBLE *list) {
	if (!list) return NULL;

	int i, error;
	DYN_LIST_DOUBLE *nlist = dyn_list_double_create(list->cmp);

	for (i = 0; i < list->counter; i++) {
		dyn_list_double_add(nlist, i, 
			dyn_list_double_get(list, i, &error));
	}

	return nlist;
}


