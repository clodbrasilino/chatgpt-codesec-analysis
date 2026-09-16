#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 || rows > SIZE_MAX / (rows + 1)) {
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
            int64_t child = dp[column] < dp[column + 1]
                                ? dp[column]
                                : dp[column + 1];

            if ((triangle[start + column] > 0 &&
                 child > INT64_MAX - triangle[start + column]) ||
                (triangle[start + column] < 0 &&
                 child < INT64_MIN - triangle[start + column])) {
                free(dp);
                return -1;
            }

            dp[column] = triangle[start + column] + child;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;

    if (scanf("%zu", &rows) != 1 || rows == 0 ||
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