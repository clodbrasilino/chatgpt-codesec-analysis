#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b, int cols) {
    const int *rowA = *(const int* const *)a;
    const int *rowB = *(const int* const *)b;
    int sumA = 0, sumB = 0;

    for (int i = 0; i < cols; ++i) {
        sumA += rowA[i];
        sumB += rowB[i];
    }

    return (sumA - sumB);
}

int compare_qsort(const void *a, const void *b) {
    int cols = 3; // Fixed: Directly specify the number of columns
    return compare(a, b, cols);
}

void sort_matrix(int ***matrix, int rows, int cols) {
    int (*cmp)(const void *, const void *) = (int(*)(const void*, const void*))compare_qsort;
    qsort(*matrix, rows, sizeof(int*), cmp);
}

int main() {
    int rows = 4, cols = 3;
    int **matrix = (int **)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int *)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    int data[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = data[i][j];
        }
    }

    sort_matrix(&matrix, rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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