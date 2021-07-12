#ifndef FUNCTIONS_H
#define FUNCTIONS_H


int ParseBoard(char*, int*);
void PrintBoard(int*);
void SolveSudoku(int*);
void SolveRows(int*);
void SolveCols(int*);
void SolveSquare(int*, int, int);
int IsInSquare(int*, int, int);
int IsInRow(int*, int, int);
int IsInCol(int*, int, int);
int ViableNumberOptionsInSquare(int*, int, int, int);

#endif