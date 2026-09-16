#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool rows_equal(const int *first, const int *second, size_t columns)
{
    for (size_t column = 0; column < columns; ++column) {
        if (first[column] != second[column]) {
            return false;
        }
    }

    return true;
}

static bool remove_similar_rows(int *matrix, size_t *rows, size_t columns)
{
    if (matrix == NULL || rows == NULL || columns == 0U) {
        return false;
    }

    size_t unique_rows = 0U;

    for (size_t current = 0U; current < *rows; ++current) {
        bool duplicate = false;

        for (size_t previous = 0U; previous < unique_rows; ++previous) {
            if (rows_equal(&matrix[current * columns],
                           &matrix[previous * columns],
                           columns)) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            if (unique_rows != current) {
                for (size_t column = 0U; column < columns; ++column) {
                    matrix[unique_rows * columns + column] =
                        matrix[current * columns + column];
                }
            }
            ++unique_rows;
        }
    }

    *rows = unique_rows;
    return true;
}

static void print_matrix(const int *matrix, size_t rows, size_t columns)
{
    for (size_t row = 0U; row < rows; ++row) {
        printf("(");
        for (size_t column = 0U; column < columns; ++column) {
            printf("%d%s",
                   matrix[row * columns + column],
                   column + 1U == columns ? "" : ", ");
        }
        printf(")\n");
    }
}

int main(void)
{
    size_t rows = 0U;
    size_t columns = 0U;

    if (scanf("%zu %zu", &rows, &columns) != 2 ||
        rows == 0U ||
        columns == 0U ||
        rows > SIZE_MAX / columns ||
        rows * columns > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid matrix dimensions\n");
        return EXIT_FAILURE;
    }

    int *matrix = malloc(rows * columns * sizeof(*matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t row = 0U; row < rows; ++row) {
        for (size_t column = 0U; column < columns; ++column) {
            if (scanf("%d", &matrix[row * columns + column]) != 1) {
                fprintf(stderr, "Invalid matrix element\n");
                free(matrix);
                return EXIT_FAILURE;
            }
        }
    }

    if (!remove_similar_rows(matrix, &rows, columns)) {
        fprintf(stderr, "Unable to process matrix\n");
        free(matrix);
        return EXIT_FAILURE;
    }

    print_matrix(matrix, rows, columns);
    free(matrix);

    return EXIT_SUCCESS;
}