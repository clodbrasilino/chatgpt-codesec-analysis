#include <stdio.h>
#include <stdlib.h>

long long max_sum_increasing_subsequence(const int *arr, size_t n)
{
    long long *dp = NULL;
    long long best = 0;
    size_t i;
    size_t j;

    if (arr == NULL || n == 0U) {
        return 0;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0U; i < n; i++) {
        dp[i] = (long long)arr[i];
        for (j = 0U; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + (long long)arr[i] > dp[i]) {
                dp[i] = dp[j] + (long long)arr[i];
            }
        }
        if (dp[i] > best) {
            best = dp[i];
        }
    }

    free(dp);
    dp = NULL;

    return best;
}

int main(void)
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = max_sum_increasing_subsequence(arr, n);

    if (printf("Sum of maximum increasing subsequence: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}