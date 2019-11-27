#ifndef sudoku_h
#define sudoku_h


#define SUCESSO 1
#define ERRO_MATRIZ -1

#define TAM 16

// ler matriz de char e retona isso ja preencia
char **criarMat();
int lerSudoku(char**);
int printSudoku(char**);
void freeSudoku(char**);
int Sudoku(char **);
#endif