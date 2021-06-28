#include <stdio.h>
#include <stdlib.h>
#include "../include/Functions.h"


int main(void) {
    char* sBoardInput = (char*)calloc(81 + 1, sizeof(char));
    printf("Board input(string): ");
    fgets(sBoardInput, 81 + 2, stdin);
    int* board = ParseBoard(sBoardInput);
    free(sBoardInput);

    SolveSudoku(board);

    printf("Missing numbers: %d\n", boardEmptyCount);
    PrintBoard(board);

    free(board);
    getchar();
    return 0;
}