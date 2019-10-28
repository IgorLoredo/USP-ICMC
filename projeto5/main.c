#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <run.h>

int main(void) {
	int i;
	char *op = (char *)malloc(sizeof(char)*2);
	int lin,col, ampli;
	scanf(" %s",op);
	scanf("%d %d",&col,&lin);
	scanf("%d",&ampli);
		runlen(lin,col,ampli,op);
		
	free(op);
  return 0;
}

  