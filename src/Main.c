#include <stdio.h>
#include <stdlib.h>
#include "../include/Functions.h"


int main(void) {
    char* sBoardInput = (char*)calloc(81 + 2, sizeof(char));

    printf("Board input: ");
    fgets(sBoardInput, 81 + 2, stdin);
    
    int* board = ParseBoard(sBoardInput);
    free(sBoardInput);

    SolveSudoku(board);

    PrintBoard(board);

    free(board);
    getchar();
    return 0;
}