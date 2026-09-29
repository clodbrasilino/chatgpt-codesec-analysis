#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool rows_equal(const int *first, const int *second, size_t columns)
{
    for (size_t column = 0; column < columns; ++column) {
        if (first[column] != second[column]) {
            return false;
        }
    }

    return true;
}

static size_t remove_similar_rows(int *matrix, size_t rows, size_t columns)
{
    size_t unique_rows = 0;

    for (size_t row = 0; row < rows; ++row) {
        bool duplicate = false;

        for (size_t unique = 0; unique < unique_rows; ++unique) {
            if (rows_equal(&matrix[row * columns],
                           &matrix[unique * columns],
                           columns)) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            if (unique_rows != row) {
                for (size_t column = 0; column < columns; ++column) {
                    matrix[unique_rows * columns + column] =
                        matrix[row * columns + column];
                }
            }
            ++unique_rows;
        }
    }

    return unique_rows;
}

int main(void)
{
    size_t rows;
    size_t columns;

    if (scanf("%zu %zu", &rows, &columns) != 2 || rows == 0 || columns == 0) {
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / columns ||
        rows * columns > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    size_t element_count = rows * columns;
    int *matrix = malloc(element_count * sizeof(*matrix));

    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (scanf("%d", &matrix[index]) != 1) {
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    size_t unique_rows = remove_similar_rows(matrix, rows, columns);

    for (size_t row = 0; row < unique_rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (column > 0 && putchar(' ') == EOF) {
                free(matrix);
                return EXIT_FAILURE;
            }

            if (printf("%d", matrix[row * columns + column]) < 0) {
                free(matrix);
                return EXIT_FAILURE;
            }
        }

        if (putchar('\n') == EOF) {
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    free(matrix);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}