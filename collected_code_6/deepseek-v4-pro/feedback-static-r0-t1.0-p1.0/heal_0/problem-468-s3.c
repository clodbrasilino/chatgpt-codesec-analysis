#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long max_increasing_subsequence_product(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return LLONG_MIN;
    }

    long long *dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return LLONG_MIN;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    long long max_product = dp[0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                long long candidate = dp[j] * arr[i];
                if (candidate > dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
        if (dp[i] > max_product) {
            max_product = dp[i];
        }
    }

    free(dp);
    return max_product;
}

int main(void) {
    int arr[] = {3, 2, 6, 4, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    long long result = max_increasing_subsequence_product(arr, n);
    if (result != LLONG_MIN) {
        printf("%lld\n", result);
    }

    return 0;
}