#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static size_t longest_subsequence_diff_one(const int *array, size_t length)
{
    size_t *dp = NULL;
    size_t longest = 0;

    if (array == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*dp)) {
        return 0;
    }

    dp = malloc(length * sizeof(*dp));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        dp[i] = 1;

        for (size_t j = 0; j < i; ++j) {
            long long difference = (long long)array[i] - (long long)array[j];

            if ((difference == 1 || difference == -1) && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > longest) {
            longest = dp[i];
        }
    }

    free(dp);
    return longest;
}

int main(void)
{
    size_t length = 0;
    int *array = NULL;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length == 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t result = longest_subsequence_diff_one(array, length);
    free(array);

    if (result == 0) {
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}