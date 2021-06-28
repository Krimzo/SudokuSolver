#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Functions.h"

int boardEmptyCount = 0;

int* ParseBoard(char* boardAsString) {
    if (strlen(boardAsString) < 81) {
        printf("Board input is too short!\nPress any key to exit..");
        getchar();
        exit(0);
    }

    int* boardAsInt = (int*)calloc(81, sizeof(int));
    if (boardAsInt == NULL) {
        printf("Coudln't allocate memoery for the board!\nPress ENTER to exit..");
        getchar();
        exit(-1);
    }

    for (int i = 0; i < 81; i++) {
        if (*(boardAsString + i) == '/' || *(boardAsString + i) == '0') {
            *(boardAsInt + i) = 0;
            boardEmptyCount++;
        }
        else if (*(boardAsString + i) > 48 && *(boardAsString + i) < 58) {
            *(boardAsInt + i) = *(boardAsString + i) - 48;
        }
        else if (*(boardAsString + i) == '\n') {
            break;
        }
        else {
            free(boardAsInt);
            printf("Bad board input!\nPress any key to exit..");
            getchar();
            exit(0);
        }
    }

    return boardAsInt;
}

void PrintBoard(int* boardAsInt) {
    if (boardEmptyCount != 0) {
        printf("Couldn't solve sudoku completely(%d empty spaces left):\n", boardEmptyCount);
    }
    else {
        printf("Solved sudoku:\n");
    }
    for (int i = 0; i < 81; i++) {
        if (*(boardAsInt + i) == 0) {
            printf("  ");
        }
        else {
            printf("%d ", *(boardAsInt + i));
        }
        if ((i + 1) % 9 == 0) {
            printf("\n");
        }
    }
}

int diagonalsSolved = 0;
void SolveSudoku(int* boardAsInt) {
    while (boardEmptyCount != 0) {
        int tempEmptyCount = boardEmptyCount;
        /* Solving START */
        if (!diagonalsSolved) {
            SolveDiagonals(boardAsInt);
        }
        SolveRows(boardAsInt);
        SolveCols(boardAsInt);
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                SolveSquare(boardAsInt, (y * 3 * 9) + x * 3);
            }
        }
        /* Solving END */
        if (boardEmptyCount == tempEmptyCount) {
            break;
        }
    }
}

int mainDiagonalSolved = 0;
int antidiagonalSolved = 0;
void SolveDiagonals(int* boardAsInt) {
    // Main diagonal
    int mainEmptyCount = 0;
    int mainNonEmptySum = 0;
    int* mainEmptyPosition = NULL;
    // Count empty
    for (int i = 0; i < 9; i++) {
        // Check if spot is empty
        if (*(boardAsInt + (9 * i + i)) == 0) {
            mainEmptyCount++;
            mainEmptyPosition = boardAsInt + (9 * i + i);
        }
        // Add to sum if it's not empty
        else {
            mainNonEmptySum += *(boardAsInt + (9 * i + i));
        }
        // Breka the loop if there is more than 1 empty space
        if (mainEmptyCount > 1) {
            break;
        }
    }
    // Solve if there is only 1 empty space left
    if (mainEmptyCount == 1) {
        *mainEmptyPosition = 45 - mainNonEmptySum;
        boardEmptyCount--;
        mainDiagonalSolved = 1;
    }
    else if (mainEmptyCount == 0) {
        mainDiagonalSolved = 1;
    }

    // Antidiagonal
    int antidiagonalEmptyCount = 0;
    int antidiagonalNonEmptySum = 0;
    int* antidiagonalEmptyPosition = NULL;
    // Count empty
    for (int i = 0; i < 9; i++) {
        // Check if spot is empty
        if (*(boardAsInt + (9 * (8 - i) + i)) == 0) {
            antidiagonalEmptyCount++;
            antidiagonalEmptyPosition = boardAsInt + (9 * (8 - i) + i);
        }
        // Add to sum if it's not empty
        else {
            antidiagonalNonEmptySum += *(boardAsInt + (9 * (8 - i) + i));
        }
        // Breka the loop if there is more than 1 empty space
        if (antidiagonalEmptyCount > 1) {
            break;
        }
    }
    // Solve if there is only 1 empty space left 
    if (antidiagonalEmptyCount == 1) {
        *antidiagonalEmptyPosition = 45 - antidiagonalNonEmptySum;
        boardEmptyCount--;
        antidiagonalSolved = 1;
    }
    else if (antidiagonalEmptyCount == 0) {
        antidiagonalSolved = 1;
    }

    // Doesn't need explaining
    if (mainDiagonalSolved && antidiagonalSolved) {
        diagonalsSolved = 1;
    }
}

void SolveRows(int* boardAsInt) {
    for (int y = 0; y < 9; y++) {
        // Main diagonal
        int emptyCount = 0;
        int nonEmptySum = 0;
        int* emptyPosition = NULL;
        // Count empty
        for (int x = 0; x < 9; x++) {
            // Check if spot is empty
            if (*(boardAsInt + (9 * y + x)) == 0) {
                emptyCount++;
                emptyPosition = boardAsInt + (9 * y + x);
            }
            // Add to sum if it's not empty
            else {
                nonEmptySum += *(boardAsInt + (9 * y + x));
            }
            // Break the loop if there is more than 1 empty space
            if (emptyCount > 1) {
                break;
            }
        }
        // Solve if there is only 1 empty space left 
        if (emptyCount == 1) {
            *emptyPosition = 45 - nonEmptySum;
            boardEmptyCount--;
        }
    }
}

void SolveCols(int* boardAsInt) {
    for (int x = 0; x < 9; x++) {
        // Main diagonal
        int emptyCount = 0;
        int nonEmptySum = 0;
        int* emptyPosition = NULL;
        // Count empty
        for (int y = 0; y < 9; y++) {
            // Check if spot is empty
            if (*(boardAsInt + (9 * y + x)) == 0) {
                emptyCount++;
                emptyPosition = boardAsInt + (9 * y + x);
            }
            // Add to sum if it's not empty
            else {
                nonEmptySum += *(boardAsInt + (9 * y + x));
            }
            // Break the loop if there is more than 1 empty space
            if (emptyCount > 1) {
                break;
            }
        }
        // Solve if there is only 1 empty space left
        if (emptyCount == 1) {
            *emptyPosition = 45 - nonEmptySum;
            boardEmptyCount--;
        }
    }
}

void SolveSquare(int* boardAsInt, int position) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {

        }
    }
}

