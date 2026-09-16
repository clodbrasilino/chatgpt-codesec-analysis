#include <stdio.h>
#include <stdlib.h>

long long maxSumIncreasingSubsequence(const int *arr, size_t n)
{
    long long *dp;
    long long best;
    size_t i;
    size_t j;

    if (arr == NULL || n == 0) {
        return 0;
    }

    dp = malloc(n * sizeof(long long));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + arr[i] > dp[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
    }

    best = dp[0];
    for (i = 1; i < n; i++) {
        if (dp[i] > best) {
            best = dp[i];
        }
    }

    free(dp);
    return best;
}

int main(void)
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = maxSumIncreasingSubsequence(arr, n);
    if (printf("Sum of maximum increasing subsequence: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}