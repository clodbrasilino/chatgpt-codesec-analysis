#include <stdio.h>
#include <stdlib.h>

static int max_len_subsequence(const int *arr, size_t n)
{
    int *dp;
    size_t i;
    size_t j;
    int result;

    if (arr == NULL || n == 0U) {
        return 0;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        dp[i] = 1;
    }

    result = 1;

    for (i = 1U; i < n; i++) {
        for (j = 0U; j < i; j++) {
            long diff = (long)arr[i] - (long)arr[j];
            if (diff < 0L) {
                diff = -diff;
            }
            if (diff <= 1L && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > result) {
            result = dp[i];
        }
    }

    free(dp);
    return result;
}

int main(void)
{
    int arr[] = { 1, 2, 3, 4, 5, 3, 2 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = max_len_subsequence(arr, n);
    if (result < 0) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum length of subsequence: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}