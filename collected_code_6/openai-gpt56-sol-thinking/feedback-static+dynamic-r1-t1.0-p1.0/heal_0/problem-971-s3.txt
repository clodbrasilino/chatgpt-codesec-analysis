#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MAX_SEGMENTS_OK,
    MAX_SEGMENTS_INVALID_ARGUMENT,
    MAX_SEGMENTS_ALLOCATION_FAILURE
} MaxSegmentsStatus;

MaxSegmentsStatus max_segments(int n, int a, int b, int c, int *result)
{
    int *dp;
    int lengths[3];
    size_t count;
    size_t i;
    size_t j;

    if (result == NULL || n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return MAX_SEGMENTS_INVALID_ARGUMENT;
    }

    if ((size_t)n > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return MAX_SEGMENTS_ALLOCATION_FAILURE;
    }

    count = (size_t)n + 1U;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return MAX_SEGMENTS_ALLOCATION_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        dp[i] = -1;
    }

    dp[0] = 0;
    lengths[0] = a;
    lengths[1] = b;
    lengths[2] = c;

    for (i = 1; i < count; ++i) {
        for (j = 0; j < 3U; ++j) {
            size_t length = (size_t)lengths[j];

            if (i >= length && dp[i - length] >= 0) {
                int candidate = dp[i - length] + 1;

                if (candidate > dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
    }

    *result = dp[n];
    free(dp);
    return MAX_SEGMENTS_OK;
}

int main(void)
{
    int n;
    int a;
    int b;
    int c;
    int result;
    MaxSegmentsStatus status;

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        return EXIT_FAILURE;
    }

    status = max_segments(n, a, b, c, &result);
    if (status != MAX_SEGMENTS_OK) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}