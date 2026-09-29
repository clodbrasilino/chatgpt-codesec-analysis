#include <stdio.h>
#include <stdlib.h>

int countSubsequences(int *arr, int n, int k) {
    int dp[k];
    for (int i = 0; i < k; ++i) {
        dp[i] = 0;
    }
    dp[1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = k - 1; j >= arr[i]; --j) {
            if (j / arr[i] > 0) {
                dp[j] += dp[j / arr[i]];
            }
        }
    }
    int sum = 0;
    for (int i = 1; i < k; ++i) {
        sum += dp[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 10;
    printf("Number of subsequences with product less than %d: %d\n", k, countSubsequences(arr, n, k));
    return 0;
}