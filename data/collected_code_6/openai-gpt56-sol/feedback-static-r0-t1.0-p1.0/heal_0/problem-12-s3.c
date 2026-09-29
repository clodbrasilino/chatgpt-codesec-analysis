#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int read_size(size_t *value)
{
    unsigned long long input;

    if (scanf("%llu", &input) != 1 || input == 0 || input > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)input;
    return 1;
}

static void sort_rows_by_sum(int *matrix, size_t rows, size_t columns)
{
    for (size_t i = 1; i < rows; ++i) {
        size_t position = i;

        while (position > 0) {
            int64_t previous_sum = 0;
            int64_t current_sum = 0;

            for (size_t column = 0; column < columns; ++column) {
                previous_sum += matrix[(position - 1) * columns + column];
                current_sum += matrix[position * columns + column];
            }

            if (previous_sum <= current_sum) {
                break;
            }

            for (size_t column = 0; column < columns; ++column) {
                int temporary = matrix[(position - 1) * columns + column];
                matrix[(position - 1) * columns + column] =
                    matrix[position * columns + column];
                matrix[position * columns + column] = temporary;
            }

            --position;
        }
    }
}

int main(void)
{
    size_t rows;
    size_t columns;
    int *matrix = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(&rows) || !read_size(&columns)) {
        goto cleanup;
    }

    if (rows > SIZE_MAX / columns ||
        rows * columns > SIZE_MAX / sizeof(*matrix)) {
        goto cleanup;
    }

    matrix = malloc(rows * columns * sizeof(*matrix));
    if (matrix == NULL) {
        goto cleanup;
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (scanf("%d", &matrix[row * columns + column]) != 1) {
                goto cleanup;
            }
        }
    }

    sort_rows_by_sum(matrix, rows, columns);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (printf("%d%s",
                       matrix[row * columns + column],
                       column + 1 == columns ? "\n" : " ") < 0) {
                goto cleanup;
            }
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(matrix);
    return status;
}