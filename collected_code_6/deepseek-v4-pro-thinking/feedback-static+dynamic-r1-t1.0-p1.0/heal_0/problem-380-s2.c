#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(size_t rows, size_t cols)
{
    int **array;
    int *data;
    size_t i;

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(*array) ||
        cols > SIZE_MAX / sizeof(int) ||
        rows > SIZE_MAX / (cols * sizeof(int))) {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    data = malloc(rows * cols * sizeof(*data));
    if (data == NULL) {
        free(array);
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        array[i] = data + i * cols;
    }

    return array;
}

void free_2d_array(int **array)
{
    if (array == NULL) {
        return;
    }

    free(array[0]);
    free(array);
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    int **array;
    size_t i;
    size_t j;

    array = generate_2d_array(rows, cols);
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            array[i][j] = (int)(i * cols + j);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    free_2d_array(array);

    return EXIT_SUCCESS;
}