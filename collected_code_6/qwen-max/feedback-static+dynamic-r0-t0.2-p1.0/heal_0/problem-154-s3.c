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

int* extract_elements(int **matrix, int rows, int cols, int step, int *result_size) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j += step) {
            ++count;
        }
    }
    int *result = (int *)malloc(count * sizeof(int));
    *result_size = count;
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j += step) {
            result[index++] = matrix[i][j];
        }
    }
    return result;
}

int main() {
    int rows = 3;
    int cols = 4;
    int step = 2;

    int **matrix = create_2d_array(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j;
        }
    }

    int result_size;
    int *result = extract_elements(matrix, rows, cols, step, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free_2d_array(matrix, rows);

    return 0;
}