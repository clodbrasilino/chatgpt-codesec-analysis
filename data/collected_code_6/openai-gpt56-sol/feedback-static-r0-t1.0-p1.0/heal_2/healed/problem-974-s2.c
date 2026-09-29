#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[256];

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
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

static int read_size(size_t *value)
{
    char buffer[256];

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1) ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    size_t last_start = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_start + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t start = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t value = triangle[start + column];
            int64_t child = dp[column] < dp[column + 1]
                                ? dp[column]
                                : dp[column + 1];

            if ((value > 0 && child > INT64_MAX - value) ||
                (value < 0 && child < INT64_MIN - value)) {
                free(dp);
                return -1;
            }

            dp[column] = value + child;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;

    if (read_size(&rows) != 0 || rows == 0 || rows == SIZE_MAX ||
        rows > SIZE_MAX / (rows + 1)) {
        fprintf(stderr, "Invalid row count\n");
        return EXIT_FAILURE;
    }

    size_t count = rows * (rows + 1) / 2;

    if (count > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Triangle is too large\n");
        return EXIT_FAILURE;
    }

    int64_t *triangle = malloc(count * sizeof(*triangle));
    if (triangle == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (read_int64(&triangle[index]) != 0) {
            fprintf(stderr, "Invalid triangle data\n");
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    int64_t result;

    if (minimum_total(triangle, rows, &result) != 0) {
        fprintf(stderr, "Unable to calculate minimum path sum\n");
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}