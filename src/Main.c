#include <stdio.h>
#include <stdlib.h>
#include "../include/Functions.h"


int main(void) {
    char* boardAsChar = (char*)calloc(81 + 1, sizeof(char));
    if (boardAsChar == NULL) {
        printf("Couldn't allocate memory for the board!\nPress ENTER to exit..");
        getchar();
        exit(-1);
    }
    int* boardAsInt = (int*)calloc(81, sizeof(int));
    if (boardAsInt == NULL) {
        printf("Couldn't allocate memory for the board!\nPress ENTER to exit..");
        getchar();
        exit(-1);
    }

    int solverRunning = 1;
    int goodInput = 0;

    while (solverRunning) {
        do {
            // Get board input
            printf("Board input: ");
            scanf("%81s", boardAsChar);
            while(getchar() != '\n');
            system("cls");
            
            // Parse char array to int array
            goodInput = !ParseBoard(boardAsChar, boardAsInt);
        } while (!goodInput);

        // Output parsed board to the screen
        PrintBoard(boardAsInt);

        // Solve parsed board
        SolveSudoku(boardAsInt);

        // Output solved board to the screen
        PrintBoard(boardAsInt);

        // Wait for input
        do {
            printf("Another board?(y or n): ");
            char decison = getchar();
            system("cls");

            if (decison == 'y' || decison == 'Y') {
                break;
            }
            else if (decison == 'n' || decison == 'N') {
                solverRunning = 0;
                break;
            }
        } while (1);
    }

    free(boardAsChar);
    free(boardAsInt);
    return 0;
}