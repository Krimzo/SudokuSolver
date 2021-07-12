#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Functions.h"

int boardEmptyCount;

int ParseBoard(char* boardAsChar, int* boardAsInt) {
    // Reset board count
    boardEmptyCount = 0;

    // Check if string is the right size
    if (strlen(boardAsChar) != 81) {
        printf("Board input is too short!");
        getchar();
        system("cls");
        return 1;
    }

    // String parsing
    for (int i = 0; i < 81; i++) {
        // Empty cells
        if (*(boardAsChar + i) == '/' || *(boardAsChar + i) == '0') {
            *(boardAsInt + i) = 0;
            boardEmptyCount++;
        }
        // Cells with numbers in them
        else if (*(boardAsChar + i) > 48 && *(boardAsChar + i) < 58) {
            *(boardAsInt + i) = *(boardAsChar + i) - 48;
        }
        // Bad input
        else {
            printf("Bad board input!");
            getchar();
            system("cls");
            return 1;
        }
    }
    return 0;
}

// Print sudoku board to the screen
void PrintBoard(int* boardAsInt) {
    if (boardEmptyCount != 0) {
        printf("%d/81 empty spaces:\n", boardEmptyCount);
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

void SolveSudoku(int* boardAsInt) {
    while (boardEmptyCount != 0) {
        int tempEmptyCount = boardEmptyCount;
        /* Solving START */
        SolveRows(boardAsInt);
        SolveCols(boardAsInt);
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                SolveSquare(boardAsInt, y * 27, x * 3); /* 27 because 3 rows * 9 cols */
            }
        }
        /* Solving END */
        if (boardEmptyCount == tempEmptyCount) {
            break;
        }
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

void SolveSquare(int* boardAsInt, int squareY, int squareX) {
    // Loop through square y
    for (int y = 0; y < 3; y++) {
        // Loop through square x
        for (int x = 0; x < 3; x++) {
            int* currentCell = boardAsInt + ((squareY + squareX) + y * 9 + x);
            // Check if the cell is empty
            if (*currentCell == 0) {
                // Loop through possible numbers
                for (int i = 1; i <= 9; i++) {
                    // Check if number already exist in the square, row and column
                    if (!IsInSquare(boardAsInt, (squareY + squareX), i) && !IsInRow(boardAsInt, squareY + (y * 9), i) && !IsInCol(boardAsInt, squareX + x, i)) {
                        // Check if only 1 cell in the square can contain that number(i)
                        if (ViableNumberOptionsInSquare(boardAsInt, squareY, squareX, i) == 1) {
                            *currentCell = i;
                            boardEmptyCount--;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Check if a number exists in a square
int IsInSquare(int* boardAsInt, int squarePosition, int number) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (*(boardAsInt + (squarePosition + y * 9 + x)) == number) {
                return 1;
            }
        }
    }
    return 0;
}

// Check if a number exists in a row
int IsInRow(int* boardAsInt, int row, int number) {
    for (int i = 0; i < 9; i++) {
        if (*(boardAsInt + (row + i)) == number) {
            return 1;
        }
    }
    return 0;
}

// Check if a number exists in a column
int IsInCol(int* boardAsInt, int col, int number) {
    for (int i = 0; i < 9; i++) {
        if (*(boardAsInt + (i * 9 + col)) == number) {
            return 1;
        }
    }
    return 0;
}

// Check in how many places can a given number go to in a given square
int ViableNumberOptionsInSquare(int* boardAsInt, int squareY, int squareX, int number) {
    int n = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int* currentCell = boardAsInt + ((squareY + squareX) + y * 9 + x);
            if (*currentCell == 0 && !IsInRow(boardAsInt, squareY + (y * 9), number) && !IsInCol(boardAsInt, squareX + x, number)) {
                n++;
            }
        }
    }
    return n;
}

