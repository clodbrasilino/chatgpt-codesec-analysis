#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static size_t max_subsequence_length(const int array[], size_t length, int difference)
{
    size_t *dp;
    size_t maximum = 0;

    if (array == NULL || length == 0) {
        return 0;
    }

    dp = calloc(length, sizeof(*dp));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        dp[i] = 1;

        for (size_t j = 0; j < i; ++j) {
            long long actual_difference =
                (long long)array[i] - (long long)array[j];

            if (actual_difference == (long long)difference &&
                dp[j] < SIZE_MAX &&
                dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
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
    int difference;
    int *array = NULL;

    if (scanf("%zu %d", &length, &difference) != 2) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", max_subsequence_length(array, length, difference));

    free(array);
    return EXIT_SUCCESS;
}