#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_token(char **token)
{
    size_t capacity = 32U;
    size_t length = 0U;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            return -1;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            temporary = realloc(buffer, new_capacity);

            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        ++length;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(buffer);
    return status;
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

static int gold_mine_max(const int64_t *mine, size_t rows, size_t cols,
                         int64_t *result)
{
    int64_t *next;
    int64_t *current;

    if (mine == NULL || result == NULL || rows == 0U || cols == 0U ||
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

    for (size_t row = 0U; row < rows; ++row) {
        next[row] = mine[row * cols + cols - 1U];
    }

    for (size_t col = cols - 1U; col > 0U; --col) {
        size_t current_col = col - 1U;

        for (size_t row = 0U; row < rows; ++row) {
            int64_t best = next[row];
            int64_t value = mine[row * cols + current_col];

            if (row > 0U && next[row - 1U] > best) {
                best = next[row - 1U];
            }

            if (row < rows - 1U && next[row + 1U] > best) {
                best = next[row + 1U];
            }

            if (checked_add_int64(value, best, &current[row]) != 0) {
                free(next);
                free(current);
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

    for (size_t row = 1U; row < rows; ++row) {
        if (next[row] > *result) {
            *result = next[row];
        }
    }

    free(next);
    free(current);
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
        rows == 0U || cols == 0U) {
        fputs("Invalid dimensions\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / cols) {
        fputs("Dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    count = rows * cols;

    if (count > SIZE_MAX / sizeof(*mine)) {
        fputs("Dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(count * sizeof(*mine));
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (read_int64(&mine[index]) != 0) {
            fputs("Invalid mine data\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (gold_mine_max(mine, rows, cols, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
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