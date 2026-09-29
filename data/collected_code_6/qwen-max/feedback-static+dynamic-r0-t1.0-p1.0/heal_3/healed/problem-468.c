#include <stdio.h>
#include <stdlib.h>

long long findMaxProduct(const int *arr, int n) {
    long long *dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        dp[i] = (long long)arr[i];
    }
    long long maxProduct = dp[0];
    for (int i = 1; i < n; ++i) {
        long long maxVal = dp[i];
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = (dp[i] > dp[j] * arr[i]) ? dp[i] : dp[j] * arr[i];
                maxVal = (maxVal > dp[i]) ? maxVal : dp[i];
            }
        }
        dp[i] = maxVal;
        if (maxProduct < dp[i]) {
            maxProduct = dp[i];
        }
    }
    free(dp);
    return maxProduct;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", findMaxProduct(arr, n));
    return 0;
}