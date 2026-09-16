#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxIncreasingSubsequenceSum(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long *dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return LLONG_MIN;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[j] + arr[i] > dp[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
    }

    long long maxSum = dp[0];
    for (size_t i = 1; i < n; i++) {
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
    }

    free(dp);
    return maxSum;
}

int main(void) {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = maxIncreasingSubsequenceSum(arr, n);
    
    if (result != LLONG_MIN) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}