#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int* row;
    long long sum;
    size_t cols;
} RowData;

int compare(const void* a, const void* b) {
    const RowData* rowA = (const RowData*)a;
    const RowData* rowB = (const RowData*)b;
    if (rowA->sum < rowB->sum) return -1;
    if (rowA->sum > rowB->sum) return 1;
    return 0;
}

void sortMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0) {
        return;
    }

    RowData* rowDataArr = (RowData*)malloc(rows * sizeof(RowData));
    if (rowDataArr == NULL) {
        return;
    }

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(rowDataArr);
            return;
        }
        rowDataArr[i].row = matrix[i];
        rowDataArr[i].cols = cols;
        rowDataArr[i].sum = 0;
        for (size_t j = 0; j < cols; j++) {
            rowDataArr[i].sum += matrix[i][j];
        }
    }

    qsort(rowDataArr, rows, sizeof(RowData), compare);

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = rowDataArr[i].row;
    }

    free(rowDataArr);
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    int values[3][4] = {
        {10, 20, 30, 40}, 
        {1, 2, 3, 4},      
        {5, 10, 15, 20}    
    };

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    sortMatrix(matrix, rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}