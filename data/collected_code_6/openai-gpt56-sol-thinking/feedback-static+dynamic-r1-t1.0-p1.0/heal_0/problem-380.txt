#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(size_t rows, size_t columns)
{
    int **array;
    int *data;
    size_t element_count;
    size_t row;
    size_t column;

    if (rows == 0 || columns == 0) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(*array) ||
        columns > SIZE_MAX / sizeof(*data) ||
        rows > SIZE_MAX / columns) {
        return NULL;
    }

    element_count = rows * columns;

    if (element_count > SIZE_MAX / sizeof(*data)) {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    data = calloc(element_count, sizeof(*data));
    if (data == NULL) {
        free(array);
        return NULL;
    }

    for (row = 0; row < rows; ++row) {
        array[row] = data + row * columns;

        for (column = 0; column < columns; ++column) {
            array[row][column] =
                (int)(((row % 100U) + (column % 100U)) % 100U);
        }
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
    const size_t rows = 4;
    const size_t columns = 5;
    int **array;
    size_t row;
    size_t column;

    array = generate_2d_array(rows, columns);
    if (array == NULL) {
        fputs("Failed to generate the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (row = 0; row < rows; ++row) {
        for (column = 0; column < columns; ++column) {
            if (printf("%d%s", array[row][column],
                       column + 1U == columns ? "" : " ") < 0) {
                free_2d_array(array);
                return EXIT_FAILURE;
            }
        }

        if (putchar('\n') == EOF) {
            free_2d_array(array);
            return EXIT_FAILURE;
        }
    }

    free_2d_array(array);
    return EXIT_SUCCESS;
}