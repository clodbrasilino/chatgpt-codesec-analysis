#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

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

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        ch = getchar();
    }

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    buffer[0] = '\0';

    do {
        ch = getchar();
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            buffer[0] = '\0';
            return discard_token(ch) == 0 ? -2 : -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[sizeof(uintmax_t) * CHAR_BIT + 2];
    char *end;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1 || buffer[0] == '-' || buffer[0] == '+') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[sizeof(intmax_t) * CHAR_BIT + 3];
    char *end;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
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
        rows > SIZE_MAX / cols ||
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
        next[row] = mine[row * cols + (cols - 1)];
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
    size_t count;
    int64_t *mine;
    int64_t result;

    if (read_size(&rows) != 0 || read_size(&cols) != 0 ||
        rows == 0 || cols == 0) {
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

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&mine[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (solve_gold_mine(mine, rows, cols, &result) != 0) {
        fputs("Unable to solve gold mine\n", stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    free(mine);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}