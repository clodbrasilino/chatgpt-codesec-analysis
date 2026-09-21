#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / (rows + 1)) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    size_t last_offset = rows * (rows - 1) / 2;
    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum = dp[column] < dp[column + 1]
                                  ? dp[column]
                                  : dp[column + 1];
            int64_t value = triangle[offset + column];

            if ((minimum > 0 && value > INT64_MAX - minimum) ||
                (minimum < 0 && value < INT64_MIN - minimum)) {
                free(dp);
                return -1;
            }

            dp[column] = value + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    int64_t parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(void)
{
    int64_t input_rows = 0;

    if (read_int64(&input_rows) != 0 || input_rows <= 0 ||
        (uintmax_t)input_rows > SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    size_t rows = (size_t)input_rows;

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *triangle = malloc(element_count * sizeof(*triangle));
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

    int64_t result = 0;
    if (minimum_total(triangle, rows, &result) != 0) {
        fputs("Unable to calculate minimum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}