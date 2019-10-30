#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dyn_list.h>

DYN_LIST *dyn_list_create(int (*cmp)(void *, void *)) {
	//list = (DYN_LIST *) malloc(sizeof(DYN_LIST)); // heap
	//list->first = NULL; 
	//list->counter = 0;
	DYN_LIST *list = (DYN_LIST *) calloc(1, sizeof(DYN_LIST)); 
	list->cmp = cmp;
	return list;
}

int dyn_list_add(DYN_LIST *list, void *new) {
	// testing if the list was created before
	if (!list) { return INVALID_LIST; }

	// creating and inserting a new element
	list->first = (DYN_LIST_ELEM *) realloc(list->first,
			sizeof(DYN_LIST_ELEM)*(list->counter+1));
	list->first[list->counter].elem = new;
	list->counter++;

	return SUCCESS;
}

int dyn_list_remove(DYN_LIST *list, int pos) {
	// testing if the list was created before
	if (!list) { return INVALID_LIST; }

	// removing an element
	if (pos >= 0 && pos < list->counter) {
		//for (i = pos; i < list->counter-1; i++) {
		//	list->first[i] = list->first[i+1];
		//}
		memcpy(&list->first[pos], &list->first[pos+1],
			sizeof(DYN_LIST_ELEM)*(list->counter-pos-1));
		list->counter--;
		list->first = (DYN_LIST_ELEM *) realloc(list->first,
			sizeof(DYN_LIST_ELEM)*list->counter);
		return SUCCESS;
	} 
	return REMOVE_ERROR;
}

int dyn_list_sort(DYN_LIST *list) {
	void *aux;
	int i, j;

	if (!list) { return INVALID_LIST; }

	// para cada elemento na lista
	//
	// i j
	// | |
	// v v
	// 0 1 2 3 4
	// ---------
	// 5 4 3 2 1
	// ---------
	for (i = 0; i < dyn_list_size(list)-1; i++) {
		for (j = i+1; j < dyn_list_size(list); j++) {
			if (list->cmp(list->first[i].elem, 
					list->first[j].elem) > 0) {
				aux = list->first[j].elem;
				list->first[j].elem = 
					list->first[i].elem;
				list->first[i].elem = aux;
			}
		}
	}

	return SUCCESS;
}

int dyn_list_size(DYN_LIST *list) {
	// testing if the list was created before
	if (!list) { return INVALID_LIST; }

	// returning the counter
	return list->counter;
}

DYN_LIST_ELEM *dyn_list_get(DYN_LIST *list, int pos, int *error) {
	if (!list) { *error = INVALID_LIST; return NULL; }
	if (pos >= 0 && pos < list->counter) return &list->first[pos];
	*error = GET_ERROR;
	return NULL;
}

int dyn_list_sequential_search(DYN_LIST *list, void *elem, 
				int *error) {
	int i;

	if (!list) {
		*error = INVALID_LIST;
		return INVALID_POS;
	}

	for (i = 0; i < list->counter; i++) {
	    if (list->cmp(list->first[i].elem, elem) == 0) {
			return i;
	    }
	}
	return INVALID_POS;
}

/*
 			key = 8
 	start			   end
 	|			   |
	v			   v
 	0  1  2  3  4  5  6  7  8  9
	-----------------------------
	|7|9|11|34|55|57|68|78|92|99|
	-----------------------------

	middle = (start+end)/2 = (0+9)/2 = 4

	2.a iteração da busca
	=====================
	start = start = 0
	end = middle-1 = 3
	key = 8

	middle = (start+end)/2 = 1

	3.a iteração da busca
	=====================
	start = start = 0
	end = middle-1 = 0
	key = 8

	middle = (0+0)/2 = 0

	4.a iteração da busca
	=====================
	start = middle+1=0+1 = 1
 	end = 0
 */

// Stack
// =====
// DYN_LIST *list (8 bytes)
// void *key (8 bytes)
// int start (4 bytes)
// int end (4 bytes)
// 	--------------------
// 	24 bytes
//
//
// Pior caso de execução (tempo necessário para 1 chamada)
// =======================================================
// C = c1 + c2 + c3 + c4 + c5 + c6 + c6 + c6 + c7
// BS(n) = BS(n/2) + C		----> Equação de recorrência
//
//
// n=100
// BS(100) = BS(50) + C
// BS(50) = BS(25) + C
// BS(25) = BS(12) + C
// BS(12) = BS(6) + C
// BS(6) = BS(3) + C
// BS(3) = BS(1) + C
// BS(1) = + C
//
// BS(n) = C*(1+log2(n))
int binary_search(DYN_LIST *list, void *key, int start, int end){ //c1
	int middle, r; // 4+4 bytes = 8 bytes (c2)

	if (start > end) { // c3
		return -1;
	}
	middle = (start + end) / 2; // c4
	r = list->cmp(key, list->first[middle].elem); // c5
	if (r == 0) { // c6
		return middle; // c7
	} else if (r < 0) { // c6
		return binary_search(list, key, start, middle-1); // c7
	} else { // ~c6
		return binary_search(list, key, middle+1, end); // c7
	}
}

int dyn_list_binary_search(DYN_LIST *list, void *key) {
	if (!list) return INVALID_POS;
	return binary_search(list, key, 0, list->counter-1);
	
	//         |
	//         v
	// 0 1 2 3 4 5 6 7 8
	// -----------------
	// 1 2 3 4 5 6 7 8 9
	// -----------------
	//         
	//     |
	//     v
	// 0 1 2 3 
	// --------
	// 1 2 3 4 
	// --------
	//
	//     
	//   |
	//   v
	// 0 1 
	// ----
	// 1 2 
	// ----
}

DYN_LIST *dyn_list_copy(DYN_LIST *list, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return NULL;
	}

	DYN_LIST *newlist = (DYN_LIST *) malloc(sizeof(DYN_LIST));
	memcpy(newlist, list, sizeof(DYN_LIST));

	newlist->first = (DYN_LIST_ELEM *) malloc(
			sizeof(DYN_LIST_ELEM)*list->counter
			);
	memcpy(&newlist->first[0], &list->first[0],
			sizeof(DYN_LIST_ELEM)*list->counter);
	*error = SUCCESS;
	return newlist;
}

int dyn_list_reverse(DYN_LIST *list) {
	int i;
	DYN_LIST_ELEM aux;

	if (!list) return INVALID_LIST;
	
	for (i = 0; i < list->counter / 2; i++) {
		memcpy(&aux,&list->first[i],sizeof(DYN_LIST_ELEM));
		memcpy(&list->first[i],
			&list->first[list->counter-i-1],
			sizeof(DYN_LIST_ELEM));
		memcpy(&list->first[list->counter-i-1], &aux,
			sizeof(DYN_LIST_ELEM));
	}

	return SUCCESS;
}

int dyn_list_insert(DYN_LIST *list, int pos, void *new) {
	if (!list) return INVALID_LIST;

	if (pos >= 0 && pos < list->counter) {
		list->first = (DYN_LIST_ELEM *) realloc(
				list->first, sizeof(DYN_LIST_ELEM)*
				(list->counter+1));
		memcpy(&list->first[pos+1], &list->first[pos],
			sizeof(DYN_LIST_ELEM) * list->counter - pos);
		list->first[pos].elem = new;
		list->counter++;
		return SUCCESS;
	}
	return INVALID_POS;
}

void dyn_list_free(DYN_LIST *list) {
	// testing if the list was created before
	if (list) {
		free(list->first);
		free(list);
	}
}



