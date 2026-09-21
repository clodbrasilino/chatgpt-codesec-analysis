#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int character;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            *capacity = 0;
            return 0;
        }
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)character;
    }

    if (ferror(stdin)) {
        return 0;
    }

    if (character == EOF && length == 0) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int read_size(const char *prompt, size_t *value)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    uintmax_t parsed;
    int result = 0;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&line, &capacity)) {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    result = 1;

cleanup:
    free(line);
    return result;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    intmax_t parsed;
    int result = 0;

    if (value == NULL) {
        return 0;
    }

    if (!read_line(&line, &capacity)) {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (end == line || errno == ERANGE ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    result = 1;

cleanup:
    free(line);
    return result;
}

static int read_matrix(int64_t *matrix, size_t rows, size_t columns)
{
    if (matrix == NULL || rows == 0 || columns == 0) {
        return 0;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (printf("Element [%zu][%zu]: ", i, j) < 0 ||
                fflush(stdout) == EOF) {
                return 0;
            }

            if (!read_int64(&matrix[i * columns + j])) {
                return 0;
            }
        }
    }

    return 1;
}

static int calculate_sum(const int64_t *row, size_t columns, int64_t *sum)
{
    int64_t total = 0;

    if (row == NULL || sum == NULL) {
        return 0;
    }

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

    {
        int64_t temporary = sums[first];
        sums[first] = sums[second];
        sums[second] = temporary;
    }
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
    if (matrix == NULL) {
        return 0;
    }

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

    if (columns > SIZE_MAX / rows) {
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