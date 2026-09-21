#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *start;
    char *end;
    intmax_t parsed;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length == 0 || buffer[length - 1] != '\n') {
        if (!feof(stdin)) {
            int ch;

            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
        }

        return -1;
    }

    buffer[length - 1] = '\0';
    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    size_t element_count;
    size_t last_offset;
    int64_t *dp;

    if (triangle == NULL || result == NULL || rows == 0 ||
        rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1) ||
        rows > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(*triangle)) {
        return -1;
    }

    dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    last_offset = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum =
                dp[column] < dp[column + 1] ? dp[column] : dp[column + 1];
            int64_t current = triangle[offset + column];

            if ((minimum > 0 && current > INT64_MAX - minimum) ||
                (minimum < 0 && current < INT64_MIN - minimum)) {
                free(dp);
                return -1;
            }

            dp[column] = current + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    int64_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t result;

    if (read_int64(&input_rows) != 0 || input_rows <= 0 ||
        (uintmax_t)input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    rows = (size_t)input_rows;

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(*triangle) ||
        rows > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (read_int64(&triangle[index]) != 0) {
            fputs("Invalid triangle value\n", stderr);
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