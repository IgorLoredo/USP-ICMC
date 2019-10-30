#include <stdlib.h>
#include <stdio.h>

// Stack
//
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      |
// --------
// |      | p (8 bytes)
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// --------

int sum(int a, int b) {
	printf("Funcao soma...\n");
	return a+b;
}

int main(int argc, char *argv[]) {
	int (*p)(int, int);

	p = &sum;
	printf("Resultado: %d\n", p(4,5));

	return 0;
}
