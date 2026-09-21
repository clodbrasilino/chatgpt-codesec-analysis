#include <ctype.h>
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

    if (*line == NULL || *capacity < 2) {
        char *new_line;
        size_t new_capacity = 128;

        new_line = realloc(*line, new_capacity);
        if (new_line == NULL) {
            return 0;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
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

            if (new_capacity <= length + 1) {
                return 0;
            }

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
    char *end;
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

    while (isspace((unsigned char)*end)) {
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
    char *end;
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
        parsed < (intmax_t)INT64_MIN ||
        parsed > (intmax_t)INT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
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

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (printf("Element [%zu][%zu]: ", row, column) < 0 ||
                fflush(stdout) == EOF) {
                return 0;
            }

            if (!read_int64(&matrix[row * columns + column])) {
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

    for (size_t column = 0; column < columns; ++column) {
        int64_t value = row[column];

        if ((value > 0 && total > INT64_MAX - value) ||
            (value < 0 && total < INT64_MIN - value)) {
            return 0;
        }

        total += value;
    }

    *sum = total;
    return 1;
}

static void swap_rows(int64_t *matrix, int64_t *sums, size_t columns,
                      size_t first, size_t second)
{
    for (size_t column = 0; column < columns; ++column) {
        int64_t temporary = matrix[first * columns + column];

        matrix[first * columns + column] =
            matrix[second * columns + column];
        matrix[second * columns + column] = temporary;
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
    for (size_t row = 1; row < rows; ++row) {
        size_t current = row;

        while (current > 0 && sums[current - 1] > sums[current]) {
            swap_rows(matrix, sums, columns, current - 1, current);
            --current;
        }
    }
}

static int print_matrix(const int64_t *matrix, size_t rows, size_t columns)
{
    if (matrix == NULL || rows == 0 || columns == 0) {
        return 0;
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (printf("%" PRId64 "%c",
                       matrix[row * columns + column],
                       column + 1 == columns ? '\n' : ' ') < 0) {
                return 0;
            }
        }
    }

    return fflush(stdout) == 0;
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

    for (size_t row = 0; row < rows; ++row) {
        if (!calculate_sum(matrix + row * columns, columns, &sums[row])) {
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