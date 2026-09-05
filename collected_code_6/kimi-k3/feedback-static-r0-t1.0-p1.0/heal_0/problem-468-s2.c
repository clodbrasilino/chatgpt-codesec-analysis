#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long maxProductIncreasingSubsequence(const long long arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long *dp = malloc(n * sizeof(long long));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    long long maxProduct = dp[0];

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                long long product;
                if (__builtin_mul_overflow(dp[j], arr[i], &product)) {
                    if (dp[j] > 0 && arr[i] > 0) {
                        product = LLONG_MAX;
                    } else if (dp[j] < 0 && arr[i] < 0) {
                        product = LLONG_MAX;
                    } else {
                        product = LLONG_MIN;
                    }
                }
                if (product > dp[i]) {
                    dp[i] = product;
                }
            }
        }
        if (dp[i] > maxProduct) {
            maxProduct = dp[i];
        }
    }

    free(dp);
    return maxProduct;
}

int main(void) {
    long long arr1[] = {3, 100, 4, 5, 150, 6};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Maximum product: %lld\n", maxProductIncreasingSubsequence(arr1, n1));

    long long arr2[] = {10, 22, 9, 33, 21, 50, 41, 60};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Maximum product: %lld\n", maxProductIncreasingSubsequence(arr2, n2));

    long long arr3[] = {1, 2, 3, 4, 5};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Maximum product: %lld\n", maxProductIncreasingSubsequence(arr3, n3));

    long long arr4[] = {-1, -2, -3, -4};
    size_t n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Maximum product: %lld\n", maxProductIncreasingSubsequence(arr4, n4));

    return 0;
}