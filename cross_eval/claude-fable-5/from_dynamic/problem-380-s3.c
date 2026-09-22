#include <stdio.h>
#include <stdlib.h>

int **create_2d_array(size_t rows, size_t cols)
{
    size_t i;
    size_t j;
    int **array = NULL;

    if (rows == 0U || cols == 0U) {
        return NULL;
    }

    if (cols > (SIZE_MAX / sizeof(int))) {
        return NULL;
    }

    array = malloc(rows * sizeof(int *));
    if (array == NULL) {
        return NULL;
    }

    for (i = 0U; i < rows; i++) {
        array[i] = malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    for (i = 0U; i < rows; i++) {
        for (j = 0U; j < cols; j++) {
            array[i][j] = (int)((i * cols) + j);
        }
    }

    return array;
}

void free_2d_array(int **array, size_t rows)
{
    size_t i;

    if (array == NULL) {
        return;
    }

    for (i = 0U; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void)
{
    size_t rows = 4U;
    size_t cols = 5U;
    size_t i;
    size_t j;
    int **matrix = NULL;

    matrix = create_2d_array(rows, cols);
    if (matrix == NULL) {
        (void)fprintf(stderr, "Failed to allocate 2D array\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < rows; i++) {
        for (j = 0U; j < cols; j++) {
            if (printf("%d ", matrix[i][j]) < 0) {
                free_2d_array(matrix, rows);
                return EXIT_FAILURE;
            }
        }
        if (printf("\n") < 0) {
            free_2d_array(matrix, rows);
            return EXIT_FAILURE;
        }
    }

    free_2d_array(matrix, rows);
    matrix = NULL;

    return EXIT_SUCCESS;
}