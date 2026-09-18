#include <stdio.h>
#include <stdlib.h>

int* extract_elements(const int* matrix, size_t rows, size_t cols, size_t target_col);

int* extract_elements(const int* matrix, size_t rows, size_t cols, size_t target_col) {
    if (matrix == NULL) {
        return NULL;
    }
    if (rows == 0 || cols == 0 || target_col >= cols) {
        return NULL;
    }

    int* result = malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        result[i] = matrix[i * cols + target_col];
    }

    return result;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    size_t target_col = 2;

    int* matrix = malloc(rows * cols * sizeof(int));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i * cols + j] = (int)((i * cols) + j);
        }
    }

    int* extracted = extract_elements(matrix, rows, cols, target_col);
    if (extracted != NULL) {
        for (size_t i = 0; i < rows; ++i) {
            printf("%d\n", extracted[i]);
        }
        free(extracted);
    }

    free(matrix);

    return EXIT_SUCCESS;
}