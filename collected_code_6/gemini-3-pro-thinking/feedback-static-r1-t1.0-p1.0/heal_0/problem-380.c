#include <stdlib.h>
#include <stddef.h>

int** generate_2d_array(size_t rows, size_t cols);
void free_2d_array(int** array, size_t rows);

int** generate_2d_array(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    int** array = malloc(rows * sizeof(int*));
    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    return array;
}

void free_2d_array(int** array, size_t rows) {
    if (array == NULL) {
        return;
    }

    for (size_t i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    size_t rows = 10;
    size_t cols = 20;

    int** matrix = generate_2d_array(rows, cols);
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (int)(i * cols + j);
        }
    }

    free_2d_array(matrix, rows);

    return EXIT_SUCCESS;
}