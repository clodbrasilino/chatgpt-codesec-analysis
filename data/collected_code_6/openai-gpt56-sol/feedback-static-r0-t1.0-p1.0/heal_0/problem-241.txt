#include <stdio.h>
#include <stdlib.h>

static char *create_3d_array(size_t depth, size_t rows, size_t columns)
{
    if (depth == 0 || rows == 0 || columns == 0) {
        return NULL;
    }

    if (depth > SIZE_MAX / rows) {
        return NULL;
    }

    size_t planes = depth * rows;

    if (planes > SIZE_MAX / columns) {
        return NULL;
    }

    size_t count = planes * columns;
    char *array = malloc(count * sizeof(*array));

    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        array[i] = '*';
    }

    return array;
}

int main(void)
{
    const size_t depth = 3;
    const size_t rows = 4;
    const size_t columns = 5;
    char *array = create_3d_array(depth, rows, columns);

    if (array == NULL) {
        fputs("Failed to create the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < depth; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            for (size_t k = 0; k < columns; ++k) {
                size_t index = (i * rows + j) * columns + k;
                printf("%c%c", array[index], k + 1 == columns ? '\n' : ' ');
            }
        }
        if (i + 1 != depth) {
            putchar('\n');
        }
    }

    free(array);
    return EXIT_SUCCESS;
}