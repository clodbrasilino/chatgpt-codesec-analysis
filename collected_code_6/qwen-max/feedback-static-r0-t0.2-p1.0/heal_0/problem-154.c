#include <stdio.h>
#include <stdlib.h>

int** create_2d_array(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        array[i] = (int *)malloc(cols * sizeof(int));
    }
    return array;
}

void free_2d_array(int **array, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}

int* extract_elements(int **matrix, int rows, int cols, int index, int *result_size) {
    int *result = (int *)malloc(rows * sizeof(int));
    *result_size = 0;
    for (int i = 0; i < rows; ++i) {
        if (index >= 0 && index < cols) {
            result[(*result_size)++] = matrix[i][index];
        }
    }
    return result;
}

int main() {
    int rows = 3;
    int cols = 4;
    int **matrix = create_2d_array(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j;
        }
    }

    int index = 2;
    int result_size;
    int *result = extract_elements(matrix, rows, cols, index, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free_2d_array(matrix, rows);

    return 0;
}