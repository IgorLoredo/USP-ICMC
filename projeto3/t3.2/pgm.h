#ifndef pgm
#define pgm

struct PGM{
	char *tipo;
	int l,c;
	char **matriz;
};
typedef struct PGM pgm;

void entrada(pgm *,FILE * );
void printMatriz(int,int,int**);


#endif