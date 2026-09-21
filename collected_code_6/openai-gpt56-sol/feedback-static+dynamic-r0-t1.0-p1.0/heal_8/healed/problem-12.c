#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *buffer = malloc(128);

        if (buffer == NULL) {
            return 0;
        }

        free(*line);
        *line = buffer;
        *capacity = 128;
    }

    for (;;) {
        int character;

        if (length == *capacity - 1) {
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

        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        (*line)[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    (*line)[length] = '\0';
    return 1;
}

static int is_space_character(unsigned char character)
{
    return character == ' ' || character == '\t' ||
           character == '\r' || character == '\n' ||
           character == '\v' || character == '\f';
}

static int read_size(const char *prompt, size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
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

    cursor = line;

    while (is_space_character((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '+' || *cursor == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    while (is_space_character((unsigned char)*end)) {
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

static int read_matrix(int64_t *matrix, size_t element_count)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t count = 0;
    int result = 0;

    if (matrix == NULL || element_count == 0) {
        return 0;
    }

    while (count < element_count) {
        char *cursor;

        if (!read_line(&line, &capacity)) {
            goto cleanup;
        }

        cursor = line;

        for (;;) {
            char *end;
            intmax_t parsed;

            while (is_space_character((unsigned char)*cursor)) {
                ++cursor;
            }

            if (*cursor == '\0') {
                break;
            }

            if (count == element_count) {
                goto cleanup;
            }

            errno = 0;
            parsed = strtoimax(cursor, &end, 10);

            if (end == cursor || errno == ERANGE ||
                parsed < INT64_MIN || parsed > INT64_MAX) {
                goto cleanup;
            }

            if (*end != '\0' &&
                !is_space_character((unsigned char)*end)) {
                goto cleanup;
            }

            matrix[count++] = (int64_t)parsed;
            cursor = end;
        }
    }

    result = 1;

cleanup:
    free(line);
    return result;
}

static int calculate_sum(const int64_t *row, size_t columns, int64_t *sum)
{
    int64_t total = 0;

    if (row == NULL || sum == NULL || columns == 0) {
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
    size_t first_offset = first * columns;
    size_t second_offset = second * columns;

    for (size_t i = 0; i < columns; ++i) {
        int64_t temporary = matrix[first_offset + i];
        matrix[first_offset + i] = matrix[second_offset + i];
        matrix[second_offset + i] = temporary;
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

static int print_matrix(const int64_t *matrix, size_t rows, size_t columns)
{
    if (matrix == NULL || rows == 0 || columns == 0) {
        return 0;
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t offset = i * columns;

        for (size_t j = 0; j < columns; ++j) {
            if (printf("%" PRId64 "%c",
                       matrix[offset + j],
                       j + 1 == columns ? '\n' : ' ') < 0) {
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

    if (fputs("Elements:\n", stdout) == EOF || fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    if (!read_matrix(matrix, element_count)) {
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