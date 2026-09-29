#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(size_t rows, size_t cols);
void free_2d_array(int **array);

int **generate_2d_array(size_t rows, size_t cols)
{
    int **array;
    size_t i;

    if (rows == 0 || cols == 0) {
        return NULL;
    }
    if (rows > SIZE_MAX / sizeof(*array)) {
        return NULL;
    }
    if (rows > SIZE_MAX / sizeof(**array)) {
        return NULL;
    }
    if (cols > SIZE_MAX / (rows * sizeof(**array))) {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    array[0] = calloc(rows * cols, sizeof(**array));
    if (array[0] == NULL) {
        free(array);
        return NULL;
    }

    for (i = 1; i < rows; ++i) {
        array[i] = array[i - 1] + cols;
    }

    return array;
}

void free_2d_array(int **array)
{
    if (array != NULL) {
        free(array[0]);
        free(array);
    }
}

int main(void)
{
    int **array;
    size_t i;
    size_t j;
    size_t rows = 3;
    size_t cols = 4;

    array = generate_2d_array(rows, cols);
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(array);
    array = NULL;

    return EXIT_SUCCESS;
}