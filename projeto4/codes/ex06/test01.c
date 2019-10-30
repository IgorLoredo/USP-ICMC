#include <stdlib.h>
#include <stdio.h>
#include <dyn_list.h>

int cmp_int(int *i, int *j) {
	if (*i == *j)
		return 0;
	else if (*i < *j) 
		return -1;
	else return 1;
}

int main(int argc, char *argv[]) {
	int a=3,b=2,c=1,d=50,x, i, error;
	DYN_LIST *mylist;
	DYN_LIST_ELEM *dyn_list_elem;

	mylist = dyn_list_create((int (*) (void *, void *)) &cmp_int); // calloc

	dyn_list_add(mylist, &a);
	dyn_list_add(mylist, &b);
	dyn_list_add(mylist, &c);

	printf("Antes\n");
	for (i = 0; i < dyn_list_size(mylist); i++) {
		dyn_list_elem = dyn_list_get(mylist, i, &error);
		printf("pos %d -> elem %d\n", 
			i, *((int *) dyn_list_elem->elem));
	}

	// 3 50 2 1
	dyn_list_insert(mylist, 1, &d);

	dyn_list_sort(mylist);

	printf("\nDepois\n");
	for (i = 0; i < dyn_list_size(mylist); i++)
		printf("pos %d -> elem %d\n", 
		   i, *((int *) dyn_list_get(mylist, i, &error)->elem));

	dyn_list_free(mylist);

	return 0;
}
