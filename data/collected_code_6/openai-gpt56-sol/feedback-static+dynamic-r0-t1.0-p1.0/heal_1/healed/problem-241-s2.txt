#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_3d_array(size_t depth, size_t rows, size_t columns,
                             char (**array)[rows][columns])
{
    if (array == NULL || depth == 0 || rows == 0 || columns == 0) {
        return -1;
    }

    *array = NULL;

    if (rows > SIZE_MAX / columns) {
        return -1;
    }

    size_t plane_size = rows * columns;

    if (depth > SIZE_MAX / plane_size) {
        return -1;
    }

    size_t element_count = depth * plane_size;

    if (element_count > SIZE_MAX / sizeof(char)) {
        return -1;
    }

    char (*allocated)[rows][columns] =
        malloc(element_count * sizeof(char));

    if (allocated == NULL) {
        return -1;
    }

    for (size_t z = 0; z < depth; ++z) {
        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                allocated[z][y][x] = '*';
            }
        }
    }

    *array = allocated;
    return 0;
}

int main(void)
{
    const size_t depth = 3;
    const size_t rows = 4;
    const size_t columns = 5;
    char (*array)[rows][columns] = NULL;

    if (generate_3d_array(depth, rows, columns, &array) != 0) {
        fputs("Failed to generate the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t z = 0; z < depth; ++z) {
        for (size_t y = 0; y < rows; ++y) {
            for (size_t x = 0; x < columns; ++x) {
                if (putchar(array[z][y][x]) == EOF ||
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