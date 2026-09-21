#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *line;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(line);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(line);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(line);
                return -1;
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                return -1;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[used++] = (char)ch;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    size_t length;
    intmax_t parsed;

    if (value == NULL || read_line(&line, &length) != 0) {
        return -1;
    }

    start = line;
    while ((size_t)(start - line) < length &&
           isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

static int read_size(size_t *value)
{
    int64_t input;

    if (value == NULL || read_int64(&input) != 0 || input <= 0 ||
        (uintmax_t)input > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)input;
    return 0;
}

static int minimum_total(const int64_t *const *triangle, size_t rows,
                         int64_t *result)
{
    int64_t *dp;

    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (triangle[i] == NULL) {
            return -1;
        }
    }

    dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (size_t j = 0; j < rows; ++j) {
        dp[j] = triangle[rows - 1][j];
    }

    for (size_t i = rows - 1; i > 0; --i) {
        for (size_t j = 0; j < i; ++j) {
            int64_t value = triangle[i - 1][j];
            int64_t minimum = dp[j] < dp[j + 1] ? dp[j] : dp[j + 1];

            if ((value > 0 && minimum > INT64_MAX - value) ||
                (value < 0 && minimum < INT64_MIN - value)) {
                free(dp);
                return -1;
            }

            dp[j] = value + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;
    int64_t **triangle;
    int64_t result;
    int status = EXIT_FAILURE;

    if (read_size(&rows) != 0 ||
        rows > SIZE_MAX / sizeof(*triangle)) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = calloc(rows, sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Unable to allocate triangle\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t elements = i + 1;

        if (elements > SIZE_MAX / sizeof(**triangle)) {
            fputs("Triangle is too large\n", stderr);
            goto cleanup;
        }

        triangle[i] = malloc(elements * sizeof(**triangle));
        if (triangle[i] == NULL) {
            fputs("Unable to allocate triangle row\n", stderr);
            goto cleanup;
        }

        for (size_t j = 0; j < elements; ++j) {
            if (read_int64(&triangle[i][j]) != 0) {
                fputs("Invalid triangle value\n", stderr);
                goto cleanup;
            }
        }
    }

    if (minimum_total((const int64_t *const *)triangle, rows, &result) != 0) {
        fputs("Unable to compute minimum path sum\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    for (size_t i = 0; i < rows; ++i) {
        free(triangle[i]);
    }

    free(triangle);
    return status;
}