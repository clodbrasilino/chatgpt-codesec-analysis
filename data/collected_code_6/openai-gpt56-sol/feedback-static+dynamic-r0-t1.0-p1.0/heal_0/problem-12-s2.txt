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

static int row_sum(const int *row, size_t columns, int64_t *sum)
{
    int64_t total = 0;

    for (size_t column = 0; column < columns; ++column) {
        if ((row[column] > 0 && total > INT64_MAX - row[column]) ||
            (row[column] < 0 && total < INT64_MIN - row[column])) {
            return 0;
        }
        total += row[column];
    }

    *sum = total;
    return 1;
}

static void swap_rows(int *matrix, size_t columns, size_t first, size_t second)
{
    if (first == second) {
        return;
    }

    for (size_t column = 0; column < columns; ++column) {
        int temporary = matrix[first * columns + column];
        matrix[first * columns + column] = matrix[second * columns + column];
        matrix[second * columns + column] = temporary;
    }
}

static void sort_matrix_by_row_sum(int *matrix, size_t rows, size_t columns,
                                   int64_t *sums)
{
    for (size_t i = 1; i < rows; ++i) {
        size_t position = i;

        while (position > 0 && sums[position - 1] > sums[position]) {
            int64_t temporary = sums[position - 1];
            sums[position - 1] = sums[position];
            sums[position] = temporary;
            swap_rows(matrix, columns, position - 1, position);
            --position;
        }
    }
}

int main(void)
{
    size_t rows;
    size_t columns;
    int *matrix = NULL;
    int64_t *sums = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(&rows) || !read_size(&columns)) {
        fprintf(stderr, "Invalid matrix dimensions.\n");
        goto cleanup;
    }

    if (columns > SIZE_MAX / rows) {
        fprintf(stderr, "Matrix dimensions are too large.\n");
        goto cleanup;
    }

    size_t element_count = rows * columns;

    if (element_count > SIZE_MAX / sizeof(*matrix) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        fprintf(stderr, "Matrix dimensions are too large.\n");
        goto cleanup;
    }

    matrix = malloc(element_count * sizeof(*matrix));
    sums = malloc(rows * sizeof(*sums));

    if (matrix == NULL || sums == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (scanf("%d", &matrix[i]) != 1) {
            fprintf(stderr, "Invalid matrix element.\n");
            goto cleanup;
        }
    }

    for (size_t row = 0; row < rows; ++row) {
        if (!row_sum(&matrix[row * columns], columns, &sums[row])) {
            fprintf(stderr, "Row sum overflow.\n");
            goto cleanup;
        }
    }

    sort_matrix_by_row_sum(matrix, rows, columns, sums);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (printf("%d%c", matrix[row * columns + column],
                       column + 1 == columns ? '\n' : ' ') < 0) {
                fprintf(stderr, "Output error.\n");
                goto cleanup;
            }
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(sums);
    free(matrix);
    return status;
}