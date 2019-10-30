#include <stdlib.h>
#include <stdio.h>
#include <dyn_list.h>

// Stack					Heap
//
// DYN_LIST *mylist --> 8 bytes			0xAB qtd bytes
// int x --> 4 bytes
// int c --> 4 bytes
// int b --> 4 bytes
// int a --> 4 bytes

int cmp_int(int *i, int *j) {
	if (*i == *j)
		return 0;
	else if (*i < *j) 
		return -1;
	else return 1;
}

int main(int argc, char *argv[]) {
	int a=1,b=2,c=3, x, i;
	DYN_LIST *mylist;

	mylist = dyn_list_create(&cmp_int); // calloc

	dyn_list_add(mylist, &a);
	dyn_list_add(mylist, &b);
	dyn_list_add(mylist, &c);

	printf("End a: %p list[0]:%p\n",&a,
			dyn_list_get(mylist,0,&x)->elem);
	printf("End b: %p list[1]:%p\n",&b,
			dyn_list_get(mylist,1,&x)->elem);
	printf("End c: %p list[2]:%p\n\n",&c,
			dyn_list_get(mylist,2,&x)->elem);

	//dyn_list_remove(mylist, 1);
	//dyn_list_remove(mylist, 0);
	dyn_list_remove(mylist, 2);

	for (i = 0; i < dyn_list_size(mylist); i++) {
		printf("Pos: %d End %p\n", i, 
				dyn_list_get(mylist,i,&x)->elem);
	}

	dyn_list_free(mylist);

	return 0;
}
