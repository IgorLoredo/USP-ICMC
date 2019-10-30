#include <stdlib.h>
#include <stdio.h>
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
	int a=3,b=2,c=1,d=50,x, i, error;
	int consulta = 50;
	DYN_LIST *mylist;
	DYN_LIST_ELEM *dyn_list_elem;

	mylist = dyn_list_create(&cmp); // calloc

	dyn_list_add(mylist, &a);
	dyn_list_add(mylist, &b);
	dyn_list_add(mylist, &d); // 2
	dyn_list_add(mylist, &c);

	dyn_list_sort(mylist);

	printf("pos: %d\n",
		dyn_list_binary_search(mylist, &consulta));

	dyn_list_free(mylist);

	return 0;
}
