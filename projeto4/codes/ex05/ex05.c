#include <stdlib.h>
#include <stdio.h>

struct Person {
	int code;	// 4 bytes
	char *name;	// 8 bytes
	int age;	// 4 bytes
};

typedef struct Person PERSON;

// Stack
// ---------
// |       | option
// ---------
// |       | list
// |       |
// |       |
// |   0   |
// |       |
// |       |
// |       |
// |       |
// ---------

int main(int argc, char *argv[]) {
	PERSON *list = NULL;
	char option;
	int counter = 0;

	printf("sizeof PERSON = %d\n", sizeof(PERSON));
	printf("sizeof PERSON * = %d\n", sizeof(PERSON *));

	while (1) {
		printf("Input? y/n ");
		scanf(" %c", &option);

		if (option == 'y') {
			list = (PERSON *) // heap
				realloc(list, 
					sizeof(PERSON)*(counter+1));
			printf("Code: "); 
			scanf("%d", &list[counter].code);
			printf("Name: "); 
			scanf("%s", &list[counter].name);
			printf("Age: "); 
			scanf("%d", &list[counter].age);
			counter++;
		} else { break; }
	}

	free(list); // liberar a memoria a heap

	return 0;
}
