#include <stdlib.h>
#include <stdio.h>

int sum(int a, int b) {
	printf("Funcao soma...\n");
	return a+b;
}

int main(int argc, char *argv[]) {
	//void (*p)(int, int);
	char (*p)(int, int);

	p = &sum;
	//p(4,5);
	printf("Retorno: %d\n", p(4,5));

	return 0;
}
