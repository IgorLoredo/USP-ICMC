#include <stdio.h>
#include <stdlib.h>
#include <dyn_list_simple.h>

int cmp(int *i, int *j) {
	if (*i == *j) return 0;
	else if (*i < *j) return -1;
	else return +1;
}

int main(int argc, char *argv[]) {
	DYN_LIST_SIMPLE *mylist;
	int a1=1, a2=2, a3=3, a4=4, i, error;

	mylist = dyn_list_simple_create((int (*)(void *, void *))&cmp);
	printf("mylist is in %p\n", mylist);

	dyn_list_simple_add(mylist, 0, &a1);
	dyn_list_simple_add(mylist, 0, &a2);
	dyn_list_simple_add(mylist, 0, &a3);  // 3  2  1
	dyn_list_simple_add_last(mylist, &a4);// 3  2  1  4

	printf("size = %d\n", dyn_list_simple_size(mylist));
	dyn_list_simple_remove(mylist, 2); // 3  2  4
	printf("size = %d\n", dyn_list_simple_size(mylist));

	for (i = 0; i < dyn_list_simple_size(mylist); i++) {
		printf("elem %d = %d\n", i,
		   *((int *) dyn_list_simple_get(mylist, i, &error)));
	}

	dyn_list_simple_free(mylist);

	return 0;
}
