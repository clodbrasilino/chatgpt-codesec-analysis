#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch = EOF;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return 0;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (int64_t)parsed;
    free(line);
    return 1;
}

static int read_positive_size(char **position, size_t *value)
{
    char *start;
    char *end;
    uintmax_t parsed;

    if (position == NULL || *position == NULL || value == NULL) {
        return 0;
    }

    start = *position;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    *position = end;
    return 1;
}

static int read_size_pair(size_t *rows, size_t *cols)
{
    char *line = NULL;
    char *position;
    size_t parsed_rows;
    size_t parsed_cols;

    if (rows == NULL || cols == NULL || !read_line(&line)) {
        return 0;
    }

    position = line;

    if (!read_positive_size(&position, &parsed_rows) ||
        !read_positive_size(&position, &parsed_cols)) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*position)) {
        ++position;
    }

    if (*position != '\0') {
        free(line);
        return 0;
    }

    *rows = parsed_rows;
    *cols = parsed_cols;
    free(line);
    return 1;
}

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int gold_mine_max(const int64_t *mine, size_t rows, size_t cols,
                         int64_t *result)
{
    int64_t *next = NULL;
    int64_t *current = NULL;
    size_t row;
    size_t col;

    if (mine == NULL || result == NULL || rows == 0 || cols == 0) {
        return 0;
    }

    if (rows > SIZE_MAX / cols ||
        rows > SIZE_MAX / sizeof *next) {
        return 0;
    }

    next = malloc(rows * sizeof *next);
    current = malloc(rows * sizeof *current);

    if (next == NULL || current == NULL) {
        free(next);
        free(current);
        return 0;
    }

    for (row = 0; row < rows; ++row) {
        next[row] = mine[row * cols + cols - 1];
    }

    for (col = cols - 1; col > 0; --col) {
        size_t current_col = col - 1;

        for (row = 0; row < rows; ++row) {
            int64_t best = next[row];

            if (row > 0 && next[row - 1] > best) {
                best = next[row - 1];
            }

            if (row + 1 < rows && next[row + 1] > best) {
                best = next[row + 1];
            }

            if (!add_int64(mine[row * cols + current_col],
                           best, &current[row])) {
                free(next);
                free(current);
                return 0;
            }
        }

        {
            int64_t *temporary = next;
            next = current;
            current = temporary;
        }
    }

    *result = next[0];

    for (row = 1; row < rows; ++row) {
        if (next[row] > *result) {
            *result = next[row];
        }
    }

    free(next);
    free(current);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t cols;
    size_t count;
    size_t i;
    int64_t *mine;
    int64_t result;

    if (!read_size_pair(&rows, &cols)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / cols) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    count = rows * cols;

    if (count > SIZE_MAX / sizeof *mine) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(count * sizeof *mine);
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (!read_int64(&mine[i])) {
            fputs("Invalid input\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (!gold_mine_max(mine, rows, cols, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    free(mine);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}