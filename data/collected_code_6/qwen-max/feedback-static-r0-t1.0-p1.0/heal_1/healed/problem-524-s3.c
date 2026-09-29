#include <stdio.h>
#include <stdlib.h>

int findSumOfMaxIncreasingSubsequence(const int *arr, int n) {
    if (n == 0) return 0;
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) exit(1);
    for (int i = 0; i < n; i++) dp[i] = arr[i];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = (dp[i] > dp[j] + arr[i]) ? dp[i] : dp[j] + arr[i];
            }
        }
    }
    int maxSum = -1;
    for (int i = 0; i < n; i++) {
        if (maxSum < dp[i]) maxSum = dp[i];
    }
    free(dp);
    return maxSum;
}

int main() {
    const int arr[] = {10, 20, 30, 40, 50, 3, 15, 17, 21};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findSumOfMaxIncreasingSubsequence(arr, n);
    printf("%d\n", result);
    return 0;
}