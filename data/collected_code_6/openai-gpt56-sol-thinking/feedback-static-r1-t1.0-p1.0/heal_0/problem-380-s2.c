#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t **generate_2d_array(size_t rows, size_t columns)
{
    size_t **array;
    size_t *elements;
    size_t element_count;
    size_t row;
    size_t column;

    if (rows == 0 || columns == 0) {
        return NULL;
    }

    if (rows > SIZE_MAX / columns) {
        return NULL;
    }

    element_count = rows * columns;

    if (rows > SIZE_MAX / sizeof(*array) ||
        element_count > SIZE_MAX / sizeof(*elements)) {
        return NULL;
    }

    array = malloc(rows * sizeof(*array));
    if (array == NULL) {
        return NULL;
    }

    elements = malloc(element_count * sizeof(*elements));
    if (elements == NULL) {
        free(array);
        return NULL;
    }

    for (row = 0; row < rows; ++row) {
        array[row] = elements + (row * columns);

        for (column = 0; column < columns; ++column) {
            array[row][column] = row * columns + column;
        }
    }

    return array;
}

static void free_2d_array(size_t **array)
{
    if (array != NULL) {
        free(array[0]);
        free(array);
    }
}

static int print_2d_array(size_t *const *array, size_t rows, size_t columns)
{
    size_t row;
    size_t column;

    if (array == NULL || rows == 0 || columns == 0) {
        return -1;
    }

    for (row = 0; row < rows; ++row) {
        for (column = 0; column < columns; ++column) {
            if (printf("%zu%c", array[row][column],
                       column == columns - 1 ? '\n' : ' ') < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const size_t rows = 3;
    const size_t columns = 4;
    size_t **array = generate_2d_array(rows, columns);

    if (array == NULL) {
        fputs("Failed to generate the array.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_2d_array(array, rows, columns) != 0) {
        free_2d_array(array);
        return EXIT_FAILURE;
    }

    free_2d_array(array);
    return EXIT_SUCCESS;
}