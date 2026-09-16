#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 45000, got <no output>
  *  test case 1 failed: expected 50265600, got <no output>
  *  test case 2 failed: expected 21780000, got <no output>
  */

long long findMaxProduct(const int *arr, int n) {
    long long *dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        dp[i] = arr[i];
    }
    long long maxProduct = dp[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = (dp[i] > dp[j] * arr[i]) ? dp[i] : dp[j] * arr[i];
            }
        }
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