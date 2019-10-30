#include <stdlib.h>
#include <stdio.h>

// Barramento de endereços: 42-48 bits
//
// Memória Pilha (Stack)
//
// --------
// |      | <- esp
// --------
// |      | p3
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// --------
// |      | p2
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// --------
// |      | p1
// |      |
// |      |
// |      |
// |      |
// |      |
// |      |
// |      | 
// --------   <- ebp

int main(int argc, char *argv[]) {
	char *p1; // 8 bytes
	int *p2;  // 8 bytes
	double ***p3; // 8 bytes

	printf("%d\n", sizeof(p1));
	printf("%d\n", sizeof(p2));
	printf("%d\n", sizeof(p3));

	while (1);

	return 0;
}
