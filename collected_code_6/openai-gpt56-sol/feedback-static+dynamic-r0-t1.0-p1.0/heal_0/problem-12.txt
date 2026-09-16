#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int read_size(const char *prompt, size_t *value)
{
    printf("%s", prompt);
    fflush(stdout);
    return scanf("%zu", value) == 1 && *value > 0;
}

static int read_matrix(int64_t *matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (scanf("%" SCNd64, &matrix[i * columns + j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

static int calculate_sum(const int64_t *row, size_t columns, int64_t *sum)
{
    int64_t total = 0;

    for (size_t i = 0; i < columns; ++i) {
        if ((row[i] > 0 && total > INT64_MAX - row[i]) ||
            (row[i] < 0 && total < INT64_MIN - row[i])) {
            return 0;
        }
        total += row[i];
    }

    *sum = total;
    return 1;
}

static void swap_rows(int64_t *matrix, int64_t *sums, size_t columns,
                      size_t first, size_t second)
{
    for (size_t i = 0; i < columns; ++i) {
        int64_t temporary = matrix[first * columns + i];
        matrix[first * columns + i] = matrix[second * columns + i];
        matrix[second * columns + i] = temporary;
    }

    int64_t temporary_sum = sums[first];
    sums[first] = sums[second];
    sums[second] = temporary_sum;
}

static void sort_rows(int64_t *matrix, int64_t *sums,
                      size_t rows, size_t columns)
{
    for (size_t i = 1; i < rows; ++i) {
        size_t j = i;

        while (j > 0 && sums[j - 1] > sums[j]) {
            swap_rows(matrix, sums, columns, j - 1, j);
            --j;
        }
    }
}

static void print_matrix(const int64_t *matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            printf("%" PRId64 "%c", matrix[i * columns + j],
                   j + 1 == columns ? '\n' : ' ');
        }
    }
}

int main(void)
{
    size_t rows;
    size_t columns;
    int64_t *matrix = NULL;
    int64_t *sums = NULL;
    int status = EXIT_FAILURE;

    if (!read_size("Rows: ", &rows) ||
        !read_size("Columns: ", &columns)) {
        fprintf(stderr, "Invalid matrix dimensions.\n");
        goto cleanup;
    }

    if (columns > SIZE_MAX / rows ||
        rows * columns > SIZE_MAX / sizeof(*matrix) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        fprintf(stderr, "Matrix dimensions are too large.\n");
        goto cleanup;
    }

    matrix = malloc(rows * columns * sizeof(*matrix));
    sums = malloc(rows * sizeof(*sums));

    if (matrix == NULL || sums == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    printf("Elements:\n");
    if (!read_matrix(matrix, rows, columns)) {
        fprintf(stderr, "Invalid matrix element.\n");
        goto cleanup;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (!calculate_sum(&matrix[i * columns], columns, &sums[i])) {
            fprintf(stderr, "Row sum overflow.\n");
            goto cleanup;
        }
    }

    sort_rows(matrix, sums, rows, columns);
    print_matrix(matrix, rows, columns);
    status = EXIT_SUCCESS;

cleanup:
    free(sums);
    free(matrix);
    return status;
}