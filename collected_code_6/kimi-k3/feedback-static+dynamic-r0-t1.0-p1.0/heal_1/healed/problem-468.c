#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxProductIncreasingSubsequence(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return LLONG_MIN;
    }
    
    long long *dp = (long long *)malloc((size_t)n * sizeof(long long));
    if (dp == NULL) {
        return LLONG_MIN;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }
    
    long long maxProduct = dp[0];
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                long long product = dp[j] * arr[i];
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
    int arr1[] = {3, 100, 4, 5, 150, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Max product: %lld\n", maxProductIncreasingSubsequence(arr1, n1));
    
    int arr2[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Max product: %lld\n", maxProductIncreasingSubsequence(arr2, n2));
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Max product: %lld\n", maxProductIncreasingSubsequence(arr3, n3));
    
    return 0;
}