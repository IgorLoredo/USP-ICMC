#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sudoku.h>



int main(){
	
	char **matSudoku = criarMat(16);
	lerSudoku(matSudoku,16);
	printSudoku(matSudoku,16);
    return 0;
}