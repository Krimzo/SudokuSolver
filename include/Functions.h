#ifndef FUNCTIONS_H
#define FUNCTIONS_H


extern int missingNumbers;

int* ParseBoard(char*);
void PrintBoard(int*);
void SolveSudoku(int*);
void SolveDiagonals(int*);
void SolveRows(int*);
void SolveCols(int*);


#endif