#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* extract_elements(int **matrix, size_t num_rows, size_t num_cols, size_t target_index) {
    if (matrix == NULL || num_rows == 0 || num_cols == 0 || target_index >= num_cols) {
        return NULL;
    }

    int *result = (int *)malloc(num_rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_rows; ++i) {
        if (matrix[i] == NULL) {
            free(result);
            return NULL;
        }
        result[i] = matrix[i][target_index];
    }

    return result;
}

int main(void) {
    size_t num_rows = 3;
    size_t num_cols = 4;
    size_t target_index = 2;

    int **matrix = (int **)malloc(num_rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_rows; ++i) {
        matrix[i] = (int *)malloc(num_cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < num_cols; ++j) {
            matrix[i][j] = (int)(i * num_cols + j);
        }
    }

    int *extracted = extract_elements(matrix, num_rows, num_cols, target_index);
    if (extracted != NULL) {
        for (size_t i = 0; i < num_rows; ++i) {
            printf("%d\n", extracted[i]);
        }
        free(extracted);
    } else {
        for (size_t i = 0; i < num_rows; ++i) {
            free(matrix[i]);
        }
        free(matrix);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}