#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **generate_2d_array(size_t rows, size_t columns)
{
    int **array;
    int *data;
    size_t element_count;
    size_t row;

    if (rows == 0 || columns == 0) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(*array) ||
        columns > SIZE_MAX / rows) {
        return NULL;
    }

    element_count = rows * columns;

    if (element_count > SIZE_MAX / sizeof(*data)) {
        return NULL;
    }

    array = calloc(rows, sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    data = calloc(element_count, sizeof(*data));
    if (data == NULL) {
        free(array);
        return NULL;
    }

    for (row = 0; row < rows; ++row) {
        array[row] = data + (row * columns);
    }

    return array;
}

void destroy_2d_array(int **array)
{
    if (array != NULL) {
        free(array[0]);
        free(array);
    }
}

int main(void)
{
    const size_t rows = 3;
    const size_t columns = 4;
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
            array[row][column] = (int)(row * columns + column);
            printf("%d%c", array[row][column],
                   column + 1 == columns ? '\n' : ' ');
        }
    }

    destroy_2d_array(array);
    return EXIT_SUCCESS;
}