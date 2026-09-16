#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int **create_2d_array(size_t rows, size_t cols, int initial_value)
{
    int **array;
    size_t i;
    size_t j;

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(*array) || cols > SIZE_MAX / sizeof(**array)) {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(**array));
        if (array[i] == NULL) {
            while (i > 0) {
                i--;
                free(array[i]);
                array[i] = NULL;
            }
            free(array);
            array = NULL;
            return NULL;
        }
        for (j = 0; j < cols; j++) {
            array[i][j] = initial_value;
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

    for (i = 0; i < rows; i++) {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
}

int main(void)
{
    const size_t rows = 3;
    const size_t cols = 4;
    int **array;
    size_t i;
    size_t j;

    array = create_2d_array(rows, cols, 0);
    if (array == NULL) {
        fprintf(stderr, "Error: failed to allocate 2D array\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array[i][j] = (int)(i * cols + j);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(array, rows);
    array = NULL;

    return EXIT_SUCCESS;
}