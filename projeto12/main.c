#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sudoku.h>



int main(){
	
	char **matSudoku = criarMat();
	lerSudoku(matSudoku);
	Sudoku(matSudoku);
    printSudoku(matSudoku);
	freeSudoku(matSudoku);
    return 0;
}
