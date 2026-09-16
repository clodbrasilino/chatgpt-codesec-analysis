#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SEGMENTS_OK,
    SEGMENTS_INVALID_ARGUMENT,
    SEGMENTS_ALLOCATION_FAILURE
} SegmentsStatus;

SegmentsStatus max_segments(size_t n, size_t a, size_t b, size_t c,
                            size_t *result)
{
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[3] = {a, b, c};
    size_t *dp;
    size_t count;
    size_t i;
    size_t j;

    if (result == NULL || a == 0 || b == 0 || c == 0) {
        return SEGMENTS_INVALID_ARGUMENT;
    }

    *result = 0;

    if (n == 0) {
        return SEGMENTS_OK;
    }

    if (n == SIZE_MAX || n + 1 > SIZE_MAX / sizeof(*dp)) {
        return SEGMENTS_ALLOCATION_FAILURE;
    }

    count = n + 1;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return SEGMENTS_ALLOCATION_FAILURE;
    }

    for (i = 0; i <= n; ++i) {
        dp[i] = SIZE_MAX;
    }
    dp[0] = 0;

    for (i = 1; i <= n; ++i) {
        for (j = 0; j < 3; ++j) {
            size_t length = lengths[j];

            if (length <= i && dp[i - length] != SIZE_MAX) {
                size_t candidate = dp[i - length] + 1;

                if (dp[i] == SIZE_MAX || candidate > dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
    }

    if (dp[n] != SIZE_MAX) {
        *result = dp[n];
    }

    free(dp);
    return SEGMENTS_OK;
}

int main(void)
{
    size_t n;
    size_t a;
    size_t b;
    size_t c;
    size_t result;
    SegmentsStatus status;

    if (scanf("%zu %zu %zu %zu", &n, &a, &b, &c) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = max_segments(n, a, b, c, &result);
    if (status == SEGMENTS_INVALID_ARGUMENT) {
        fputs("Invalid segment length\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == SEGMENTS_ALLOCATION_FAILURE) {
        fputs("Unable to allocate memory\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}