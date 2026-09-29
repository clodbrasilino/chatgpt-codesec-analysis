#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static void skip_space(char **position)
{
    if (position == NULL || *position == NULL) {
        return;
    }

    while (**position != '\0' &&
           isspace((unsigned char)**position) != 0) {
        ++*position;
    }
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *position;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    position = line;
    skip_space(&position);

    errno = 0;
    parsed = strtoimax(position, &end, 10);

    if (end == position || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return 0;
    }

    position = end;
    skip_space(&position);

    if (*position != '\0') {
        free(line);
        return 0;
    }

    *value = (int64_t)parsed;
    free(line);
    return 1;
}

static int parse_size(char **position, size_t *value)
{
    char *start;
    char *end;
    uintmax_t parsed;

    if (position == NULL || *position == NULL || value == NULL) {
        return 0;
    }

    skip_space(position);
    start = *position;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *position = end;
    *value = (size_t)parsed;
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

    if (!parse_size(&position, &parsed_rows) ||
        !parse_size(&position, &parsed_cols)) {
        free(line);
        return 0;
    }

    skip_space(&position);

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
    int64_t *next;
    int64_t *current;
    size_t row;
    size_t col;

    if (mine == NULL || result == NULL || rows == 0 || cols == 0 ||
        rows > SIZE_MAX / sizeof(*next) ||
        rows > SIZE_MAX / cols) {
        return 0;
    }

    next = malloc(rows * sizeof(*next));
    current = malloc(rows * sizeof(*current));

    if (next == NULL || current == NULL) {
        free(next);
        free(current);
        return 0;
    }

    for (row = 0; row < rows; ++row) {
        next[row] = mine[row * cols + (cols - 1)];
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

    if (count > SIZE_MAX / sizeof(*mine)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(count * sizeof(*mine));
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