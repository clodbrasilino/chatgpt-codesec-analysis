#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list_of_lists, size_t num_rows, size_t num_cols, size_t col_index, int *result) {
    if (list_of_lists == NULL || result == NULL) {
        return -1; 
    }
    if (col_index >= num_cols) {
        return -1; 
    }

    int sum = 0;
    for (size_t i = 0; i < num_rows; i++) {
        if (list_of_lists[i] == NULL) {
            return -1; 
        }
        sum += list_of_lists[i][col_index];
    }

    *result = sum;
    return 0;
}

int main(void) {
    size_t num_rows = 3;
    size_t num_cols = 4;
    size_t col_to_sum = 2;

    int **matrix = malloc(num_rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_rows; i++) {
        matrix[i] = malloc(num_cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < num_cols; j++) {
            matrix[i][j] = (int)(i + j);
        }
    }

    int result = 0;
    if (sum_column(matrix, num_rows, num_cols, col_to_sum, &result) == 0) {
        printf("Sum of column %zu: %d\n", col_to_sum, result);
    } else {
        printf("Failed to calculate sum.\n");
    }

    for (size_t i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}