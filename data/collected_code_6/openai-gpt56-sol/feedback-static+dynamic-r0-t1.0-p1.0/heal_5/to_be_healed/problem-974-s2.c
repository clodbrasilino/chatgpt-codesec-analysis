#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int triangle_count(size_t rows, size_t *count)
{
    size_t a;
    size_t b;

    if (count == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1;

    if ((a & 1U) == 0U) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > SIZE_MAX / a) {
        return -1;
    }

    *count = a * b;
    return 0;
}

static int read_token(char **token)
{
    enum { MAX_TOKEN_LENGTH = 256 };
    char *buffer;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc((size_t)MAX_TOKEN_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == MAX_TOKEN_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            free(buffer);
            return -1;
        }

        buffer[length++] = (char)ch;
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

static int read_size_value(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    end = NULL;
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

static int add_int64_checked(int64_t left, int64_t right, int64_t *sum)
{
    if (sum == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *sum = left + right;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows,
                         int64_t *result)
{
    size_t count;
    size_t last_start;
    size_t start;
    int64_t *dp;

    if (triangle == NULL || result == NULL ||
        triangle_count(rows, &count) != 0 ||
        rows > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    last_start = count - rows;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_start + column];
    }

    start = last_start;

    for (size_t row = rows - 1; row > 0; --row) {
        start -= row;

        for (size_t column = 0; column < row; ++column) {
            int64_t child = dp[column] < dp[column + 1]
                                ? dp[column]
                                : dp[column + 1];

            if (add_int64_checked(triangle[start + column], child,
                                  &dp[column]) != 0) {
                free(dp);
                return -1;
            }
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t count;
    int64_t result;
    int64_t *triangle;

    if (read_size_value(&rows) != 0 ||
        triangle_count(rows, &count) != 0) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (read_int64_value(&triangle[index]) != 0) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (minimum_total(triangle, rows, &result) != 0) {
        fputs("Unable to calculate minimum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}