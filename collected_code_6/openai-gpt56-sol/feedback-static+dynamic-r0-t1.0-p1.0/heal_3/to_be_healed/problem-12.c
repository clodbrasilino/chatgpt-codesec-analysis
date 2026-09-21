#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_size(const char *prompt, size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    fputs(prompt, stdout);
    fflush(stdout);

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_matrix(int64_t *matrix, size_t rows, size_t columns)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    size_t count = 0;
    size_t total = rows * columns;

    while (count < total && fgets(buffer, sizeof buffer, stdin) != NULL) {
        char *cursor = buffer;

        while (count < total) {
            char *end;
            intmax_t parsed;

            while (*cursor == ' ' || *cursor == '\t' ||
                   *cursor == '\r' || *cursor == '\n') {
                ++cursor;
            }

            if (*cursor == '\0') {
                break;
            }

            errno = 0;
            parsed = strtoimax(cursor, &end, 10);

            if (end == cursor || errno == ERANGE ||
                parsed < INT64_MIN || parsed > INT64_MAX) {
                return 0;
            }

            if (*end != '\0' && *end != ' ' && *end != '\t' &&
                *end != '\r' && *end != '\n') {
                return 0;
            }

            matrix[count++] = (int64_t)parsed;
            cursor = end;
        }
    }

    return count == total;
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

static int print_matrix(const int64_t *matrix,
                        size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (printf("%" PRId64 "%c",
                       matrix[i * columns + j],
                       j + 1 == columns ? '\n' : ' ') < 0) {
                return 0;
            }
        }
    }

    return 1;
}

int main(void)
{
    size_t rows;
    size_t columns;
    size_t element_count;
    int64_t *matrix = NULL;
    int64_t *sums = NULL;
    int status = EXIT_FAILURE;

    if (!read_size("Rows: ", &rows) ||
        !read_size("Columns: ", &columns)) {
        fputs("Invalid matrix dimensions.\n", stderr);
        goto cleanup;
    }

    if (rows > SIZE_MAX / columns) {
        fputs("Matrix dimensions are too large.\n", stderr);
        goto cleanup;
    }

    element_count = rows * columns;

    if (element_count > SIZE_MAX / sizeof *matrix ||
        rows > SIZE_MAX / sizeof *sums) {
        fputs("Matrix dimensions are too large.\n", stderr);
        goto cleanup;
    }

    matrix = malloc(element_count * sizeof *matrix);
    sums = malloc(rows * sizeof *sums);

    if (matrix == NULL || sums == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    fputs("Elements:\n", stdout);

    if (!read_matrix(matrix, rows, columns)) {
        fputs("Invalid matrix element.\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (!calculate_sum(matrix + i * columns, columns, &sums[i])) {
            fputs("Row sum overflow.\n", stderr);
            goto cleanup;
        }
    }

    sort_rows(matrix, sums, rows, columns);

    if (!print_matrix(matrix, rows, columns)) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(sums);
    free(matrix);
    return status;
}