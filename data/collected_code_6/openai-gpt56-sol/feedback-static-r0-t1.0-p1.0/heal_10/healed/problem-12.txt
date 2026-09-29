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
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;
            char *new_line;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity < required) {
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
    char *start;
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

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
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
    char *start;
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

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
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
    size_t row;
    size_t column;

    if (matrix == NULL || rows == 0 || columns == 0 ||
        columns > SIZE_MAX / rows) {
        return 0;
    }

    for (row = 0; row < rows; ++row) {
        size_t offset = row * columns;

        for (column = 0; column < columns; ++column) {
            if (printf("Element [%zu][%zu]: ", row, column) < 0 ||
                fflush(stdout) == EOF) {
                return 0;
            }

            if (!read_int64(&matrix[offset + column])) {
                return 0;
            }
        }
    }

    return 1;
}

static int calculate_sum(const int64_t *row, size_t columns, int64_t *sum)
{
    size_t column;
    int64_t total = 0;

    if (row == NULL || sum == NULL || columns == 0) {
        return 0;
    }

    for (column = 0; column < columns; ++column) {
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
    size_t column;
    size_t first_offset = first * columns;
    size_t second_offset = second * columns;
    int64_t temporary;

    for (column = 0; column < columns; ++column) {
        temporary = matrix[first_offset + column];
        matrix[first_offset + column] = matrix[second_offset + column];
        matrix[second_offset + column] = temporary;
    }

    temporary = sums[first];
    sums[first] = sums[second];
    sums[second] = temporary;
}

static void sort_rows(int64_t *matrix, int64_t *sums,
                      size_t rows, size_t columns)
{
    size_t row;

    if (matrix == NULL || sums == NULL || rows < 2 || columns == 0) {
        return;
    }

    for (row = 1; row < rows; ++row) {
        size_t current = row;

        while (current > 0 && sums[current - 1] > sums[current]) {
            swap_rows(matrix, sums, columns, current - 1, current);
            --current;
        }
    }
}

static int print_matrix(const int64_t *matrix, size_t rows, size_t columns)
{
    size_t row;
    size_t column;

    if (matrix == NULL || rows == 0 || columns == 0 ||
        columns > SIZE_MAX / rows) {
        return 0;
    }

    for (row = 0; row < rows; ++row) {
        size_t offset = row * columns;

        for (column = 0; column < columns; ++column) {
            if (printf("%" PRId64 "%c",
                       matrix[offset + column],
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
    size_t row;
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
        fputs("Invalid matrix element or input error.\n", stderr);
        goto cleanup;
    }

    for (row = 0; row < rows; ++row) {
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