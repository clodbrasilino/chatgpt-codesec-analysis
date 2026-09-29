#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static int minimum_total(const int64_t *const *triangle, size_t rows,
                         int64_t *result)
{
    int64_t *dp;

    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (triangle[i] == NULL) {
            free(dp);
            return -1;
        }
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
    int64_t **triangle = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &rows) != 1 || rows == 0 ||
        rows > SIZE_MAX / sizeof(*triangle)) {
        fprintf(stderr, "Invalid row count\n");
        return EXIT_FAILURE;
    }

    triangle = calloc(rows, sizeof(*triangle));
    if (triangle == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t elements = i + 1;

        if (elements > SIZE_MAX / sizeof(**triangle)) {
            fprintf(stderr, "Triangle is too large\n");
            goto cleanup;
        }

        triangle[i] = malloc(elements * sizeof(**triangle));
        if (triangle[i] == NULL) {
            perror("malloc");
            goto cleanup;
        }

        for (size_t j = 0; j < elements; ++j) {
            if (scanf("%" SCNd64, &triangle[i][j]) != 1) {
                fprintf(stderr, "Invalid triangle value\n");
                goto cleanup;
            }
        }
    }

    if (minimum_total((const int64_t *const *)triangle, rows, &result) != 0) {
        fprintf(stderr, "Unable to compute minimum path sum\n");
        goto cleanup;
    }

    printf("%" PRId64 "\n", result);
    status = EXIT_SUCCESS;

cleanup:
    for (size_t i = 0; i < rows; ++i) {
        free(triangle[i]);
    }

    free(triangle);
    return status;
}