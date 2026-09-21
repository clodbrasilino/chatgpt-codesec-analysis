#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int64_t max3(int64_t a, int64_t b, int64_t c)
{
    int64_t result = a;

    if (b > result) {
        result = b;
    }
    if (c > result) {
        result = c;
    }

    return result;
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = getchar();
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        ch = getchar();
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size_value(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(&buffer);
    if (status != 1) {
        return -1;
    }

    if (buffer[0] == '-' || buffer[0] == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(&buffer);
    if (status != 1) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int input_ended(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return ferror(stdin) ? 0 : 1;
}

static int checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return -1;
    }

    *result = a + b;
    return 0;
}

static int solve_gold_mine(const int64_t *mine, size_t rows, size_t cols,
                           int64_t *result)
{
    int64_t *next;
    int64_t *current;

    if (mine == NULL || result == NULL || rows == 0 || cols == 0 ||
        rows > SIZE_MAX / sizeof(*next)) {
        return -1;
    }

    next = malloc(rows * sizeof(*next));
    current = malloc(rows * sizeof(*current));

    if (next == NULL || current == NULL) {
        free(next);
        free(current);
        return -1;
    }

    for (size_t row = 0; row < rows; ++row) {
        next[row] = mine[row * cols + cols - 1];
    }

    for (size_t col = cols - 1; col > 0; --col) {
        size_t previous_col = col - 1;

        for (size_t row = 0; row < rows; ++row) {
            int64_t right = next[row];
            int64_t right_up = row > 0 ? next[row - 1] : INT64_MIN;
            int64_t right_down =
                row < rows - 1 ? next[row + 1] : INT64_MIN;
            int64_t best = max3(right, right_up, right_down);
            int64_t value = mine[row * cols + previous_col];

            if (checked_add_int64(value, best, &current[row]) != 0) {
                free(current);
                free(next);
                return -1;
            }
        }

        {
            int64_t *temporary = next;
            next = current;
            current = temporary;
        }
    }

    *result = next[0];

    for (size_t row = 1; row < rows; ++row) {
        if (next[row] > *result) {
            *result = next[row];
        }
    }

    free(current);
    free(next);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t cols;
    size_t element_count;
    int64_t *mine;
    int64_t result;

    if (read_size_value(&rows) != 0 ||
        read_size_value(&cols) != 0 ||
        rows == 0 || cols == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / cols) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = rows * cols;

    if (element_count > SIZE_MAX / sizeof(*mine)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(element_count * sizeof(*mine));
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (read_int64_value(&mine[index]) != 0) {
            fputs("Invalid input\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (!input_ended()) {
        fputs("Invalid input\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    if (solve_gold_mine(mine, rows, cols, &result) != 0) {
        fputs("Unable to solve gold mine\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(mine);
        return EXIT_FAILURE;
    }

    free(mine);
    return EXIT_SUCCESS;
}