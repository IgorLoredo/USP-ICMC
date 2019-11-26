#ifndef sudoku_h
#define sudoku_h


#define SUCESSO 1
#define ERRO_MATRIZ -1


// ler matriz de char e retona isso ja preencia
char **criarMat(int);
int lerSudoku(char**,int);
int printSudoku(char**,int);


#endif