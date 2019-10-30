#include <stdlib.h>
#include <stdio.h>

/*
 	char **argv // 8 bytes
		|
		|
		|
		|-------> char * (8 bytes) -------> "string\0"
		|
		|-------> char * (8 bytes)-------> "outra\0"
 */

int main(int argc, char **argv) {

	return 0;
}
