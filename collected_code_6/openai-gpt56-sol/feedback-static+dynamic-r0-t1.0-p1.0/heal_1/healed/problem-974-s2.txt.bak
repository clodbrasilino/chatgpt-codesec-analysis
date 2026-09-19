#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int triangle_element_count(size_t rows, size_t *count)
{
    if (count == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    size_t a = rows;
    size_t b = rows + 1;

    if ((a & 1U) == 0) {
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

static int checked_add_int64(int64_t a, int64_t b, int64_t *sum)
{
    if (sum == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return -1;
    }

    *sum = a + b;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    size_t count;

    if (triangle == NULL || result == NULL ||
        triangle_element_count(rows, &count) != 0 ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    size_t last_start = count - rows;
    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_start + column];
    }

    for (size_t row = rows - 1; row != 0; --row) {
        size_t start = row * (row - 1) / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t child = dp[column] < dp[column + 1]
                                ? dp[column]
                                : dp[column + 1];

            if (checked_add_int64(triangle[start + column],
                                  child,
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

    if (scanf("%zu", &rows) != 1 ||
        triangle_element_count(rows, &count) != 0) {
        fprintf(stderr, "Invalid row count\n");
        return EXIT_FAILURE;
    }

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
        if (scanf("%" SCNd64, &triangle[index]) != 1) {
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

    if (printf("%" PRId64 "\n", result) < 0) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}