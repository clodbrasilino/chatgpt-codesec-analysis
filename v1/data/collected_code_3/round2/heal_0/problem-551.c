#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 5

void extract_column(int matrix[ROWS][COLS], int col, int *result) {
    for (int i = 0; i < ROWS; i++) {
        result[i] = matrix[i][col];
    }
}

int main() {
    int matrix[ROWS][COLS] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    int col_to_extract = 2;
    int result[ROWS];

    extract_column(matrix, col_to_extract, result);

    for (int i = 0; i < ROWS; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}