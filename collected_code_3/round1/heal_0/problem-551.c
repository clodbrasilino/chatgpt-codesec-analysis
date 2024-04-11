#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 5

void extract_column(int **matrix, int col_num, int rows, int cols) {
    if (col_num < 0 || col_num >= cols) {
        printf("Invalid column number.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        printf("%d ", matrix[i][col_num]);
    }
    printf("\n");
}

int main() {
    int **matrix = (int **)malloc(ROWS * sizeof(int *));
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int *)malloc(COLS * sizeof(int));
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = i * COLS + j;
        }
    }

    int col_num = 2;
    printf("Column %d: ", col_num);
    extract_column(matrix, col_num, ROWS, COLS);

    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}