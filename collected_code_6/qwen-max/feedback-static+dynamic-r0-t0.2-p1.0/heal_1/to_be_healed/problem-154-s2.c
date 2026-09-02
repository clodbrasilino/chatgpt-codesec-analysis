#include <stdio.h>
#include <stdlib.h>

int** extract_elements(int **matrix, int rows, int cols, int step, int *new_rows) {
    *new_rows = (rows + step - 1) / step;
    int **result = (int **)malloc(*new_rows * sizeof(int *));
    for (int i = 0; i < *new_rows; ++i) {
        result[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            /* Possible weaknesses found:
             * ASan: SEGV
             * UBSan: load of misaligned address 0x000200000001 for type 'int', which requires 4 byte alignment
             */
            result[i][j] = matrix[i * step][j];
        }
    }
    return result;
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int rows = 3;
    int cols = 4;
    int step = 2;

    int new_rows;
    int **result = extract_elements((int **)matrix, rows, cols, step, &new_rows);

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    free_matrix(result, new_rows);
    return 0;
}