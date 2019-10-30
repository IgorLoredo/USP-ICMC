#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int i; // 4 bytes
	unsigned char j; // 1 byte
	char *p; // 8 bytes

	// Intel: little endian
	// --------------
	// |00111111    | LSB (least sign. byte)   63
	// |00110011    |			   51
	// |01001010    |			   74
	// |00001000    | MSB (most)		    8
	// --------------
	i = 139080511;
	p = (char *) &i;

	for (j = 0; j < 4; j++) {
		printf("%d (%p) -> %d\n", j, p, *p);
		p++;
	}


	return 0;
}
