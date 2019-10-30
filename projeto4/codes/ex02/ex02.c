#include <stdlib.h>
#include <stdio.h>

// Stack					Heap
// --------
// |      | i
// |      |
// |      |
// |      |
// |      |
// --------					---------
// |      | string			0xABC	|       |
// |      |					---------
// | 0xABC|					|       |
// |      |					---------
// |      |					...
// |      |					|       |
// |      |					---------
// |      |
// --------
// |      | p
// | 0xABC|
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// --------

int main(int argc, char *argv[]) {
	char *p;     // 8 bytes
	char *string; // 8 bytes
	int i; // 4 bytes
	int *pi; // 8 bytes
	void *pv;  // 8 bytes

	string = (char *) malloc(50);
	p = string;
	pi = (int *) string;

	for (i = 0; i < 5; i++) {
		printf("Endereço contido em p: %p\n", p);
		p++;
	}

	printf("\n");
	for (i = 0; i < 5; i++) {
		printf("Endereço contido em pi: %p\n", pi);
		pi++;
	}

	return 0;
}
