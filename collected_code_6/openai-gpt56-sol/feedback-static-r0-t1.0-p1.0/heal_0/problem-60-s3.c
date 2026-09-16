#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t maximum_subsequence_length(const int *array, size_t length, long long difference)
{
    size_t maximum = 0U;
    size_t *dp;

    if (array == NULL || length == 0U) {
        return 0U;
    }

    if (length > SIZE_MAX / sizeof(*dp)) {
        return 0U;
    }

    dp = malloc(length * sizeof(*dp));
    if (dp == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        dp[i] = 1U;

        for (size_t j = 0U; j < i; ++j) {
            long long actual_difference =
                (long long)array[i] - (long long)array[j];

            if (actual_difference == difference && dp[j] < SIZE_MAX &&
                dp[i] < dp[j] + 1U) {
                dp[i] = dp[j] + 1U;
            }
        }

        if (dp[i] > maximum) {
            maximum = dp[i];
        }
    }

    free(dp);
    return maximum;
}

int main(void)
{
    size_t length;
    long long difference;
    int *array;

    if (scanf("%zu %lld", &length, &difference) != 2 || length == 0U ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", maximum_subsequence_length(array, length, difference));

    free(array);
    return EXIT_SUCCESS;
}