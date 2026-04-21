#include <stdio.h>
#include <string.h>

#define SIZE 9

void inputGrid(int grid[9][9]) {
    printf("Enter Sudoku (use 0 for empty cells, space after every number and enter after every 9 numbers):\n");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

void printGrid(int grid[9][9]) {
    printf("\n");

    for (int i = 0; i < 9; i++) {

        // горизонтальная линия
        if (i % 3 == 0 && i != 0)
            printf("---------------------\n");

        for (int j = 0; j < 9; j++) {

            // вертикальная линия
            if (j % 3 == 0 && j != 0)
                printf("| ");

            if (grid[i][j] == 0)
                printf(". ");
            else
                printf("%d ", grid[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

int isValid(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int i = 0; i < SIZE; i++)
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;

    int sr = row - row % 3;
    int sc = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[sr + i][sc + j] == num)
                return 0;

    return 1;
}

// логика
int applyLogic(int grid[SIZE][SIZE]) {
    int changed = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {

            if (grid[r][c] == 0) {
                int count = 0, last = 0;

                for (int num = 1; num <= 9; num++) {
                    if (isValid(grid, r, c, num)) {
                        count++;
                        last = num;
                    }
                }

                if (count == 1) {
                    grid[r][c] = last;
                    changed = 1;
                }
            }
        }
    }

    return changed;
}

int findEmpty(int grid[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (grid[*row][*col] == 0)
                return 1;
    return 0;
}

// 🔥 ИСПРАВЛЕННЫЙ ГИБРИД
int solveSudoku(int grid[SIZE][SIZE]) {

    int backup[SIZE][SIZE];
    memcpy(backup, grid, sizeof(backup)); // сохраняем состояние

    // логика
    while (applyLogic(grid));

    int row, col;

    if (!findEmpty(grid, &row, &col))
        return 1;

    for (int num = 1; num <= 9; num++) {

        if (isValid(grid, row, col, num)) {

            int temp[SIZE][SIZE];
            memcpy(temp, grid, sizeof(temp)); // копия перед пробой

            grid[row][col] = num;

            if (solveSudoku(grid))
                return 1;

            memcpy(grid, temp, sizeof(temp)); // откат ВСЕГО состояния
        }
    }

    return 0;
}

int main() {

    int sudoku[9][9];

    inputGrid(sudoku); // 👈 ввод от пользователя

    printf("\nYour Sudoku:\n");
    printGrid(sudoku);

    if (solveSudoku(sudoku)) {
        printf("Solved:\n");
        printGrid(sudoku);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
