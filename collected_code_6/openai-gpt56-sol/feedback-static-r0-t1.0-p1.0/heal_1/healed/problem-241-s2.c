#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_3d_array(size_t depth, size_t rows, size_t columns,
                             char **array)
{
    size_t plane_size;
    size_t total_size;

    if (array == NULL || depth == 0 || rows == 0 || columns == 0) {
        return -1;
    }

    *array = NULL;

    if (rows > SIZE_MAX / columns) {
        return -1;
    }
    plane_size = rows * columns;

    if (depth > SIZE_MAX / plane_size) {
        return -1;
    }
    total_size = depth * plane_size;

    char *data = malloc(total_size);
    if (data == NULL) {
        return -1;
    }

    for (size_t i = 0; i < total_size; ++i) {
        data[i] = '*';
    }

    *array = data;
    return 0;
}

static size_t array_index(size_t z, size_t y, size_t x,
                          size_t rows, size_t columns)
{
    return (z * rows + y) * columns + x;
}

int main(void)
{
    const size_t depth = 3;
    const size_t rows = 4;
    const size_t columns = 5;
    char *array = NULL;

    if (generate_3d_array(depth, rows, columns, &array) != 0) {
        fputs("Failed to generate the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t z = 0; z < depth; ++z) {
        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                if (putchar(array[array_index(z, y, x, rows, columns)]) == EOF ||
                    (x + 1 < columns && putchar(' ') == EOF)) {
                    free(array);
                    return EXIT_FAILURE;
                }
            }

            if (putchar('\n') == EOF) {
                free(array);
                return EXIT_FAILURE;
            }
        }

        if (z + 1 < depth && putchar('\n') == EOF) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}