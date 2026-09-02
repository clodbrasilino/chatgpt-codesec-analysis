#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    const int *rowA = *(const int **)a;
    const int *rowB = *(const int **)b;
    int sumA = 0, sumB = 0;
    for (int i = 1; i < rowA[0]; ++i) {
        sumA += rowA[i];
        sumB += rowB[i];
    }
    return (sumA - sumB);
}

void sort_matrix(int ***matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)realloc(matrix[i], (cols + 1) * sizeof(int));
        matrix[i][cols] = cols;
    }
    qsort(*matrix, rows, sizeof(int*), compare);
}

int main() {
    int rows = 4, cols = 3;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc((cols + 1) * sizeof(int));
        matrix[i][0] = cols;
    }

    int data[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j + 1] = data[i][j];
        }
    }

    sort_matrix(&matrix, rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}