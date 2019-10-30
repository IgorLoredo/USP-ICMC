#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dyn_list.h>

int cmp(void *i, void *j) {
	if (*((int *) i) == *((int *) j))
		return 0;
	else if (*((int *) i) < *((int *) j))
		return -1;
	else 
		return 1;
}

int main(int argc, char *argv[]) {
	int i, key, error;
	int *p;
	clock_t start, end;
	DYN_LIST *mylist;
	DYN_LIST_ELEM *dyn_list_elem;

	mylist = dyn_list_create(&cmp); // calloc
	for (i = 999; i >= 0; i--) {
		p = (int *) malloc(sizeof(int));
		*p = i;
		dyn_list_add(mylist, p);
	}

	dyn_list_sort(mylist);

	key = 999;
	time(&start);
	for (key = 0; key < 1000; key++) {
		dyn_list_binary_search(mylist, &key);
		//printf("pos: %d\n", dyn_list_binary_search(mylist, &key));
	}
	time(&end);
	printf("Time: %lf\n", (end-start)/(CLOCKS_PER_SEC * 1.0));

	// liberar cada elemento (malloc)
	for (i = 0; i < dyn_list_size(mylist); i++) {
		dyn_list_elem = dyn_list_get(mylist, i, &error);
		free(dyn_list_elem->elem);
	}
	dyn_list_free(mylist);

	return 0;
}
