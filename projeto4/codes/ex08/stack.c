#include <stdlib.h>
#include <stdio.h>

int f(int a, int b) {
	int c;

	printf("a: %p\tb: %p\tc: %p\theap:%p\n", &a, &b, &c, malloc(1));

	c = f(a--,b);
	return c;
}

int main(int argc, char *argv[]) {

	int i;

	i = f(5,2);

	return 0;
}
