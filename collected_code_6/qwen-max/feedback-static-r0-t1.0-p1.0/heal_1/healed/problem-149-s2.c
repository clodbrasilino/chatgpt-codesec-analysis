#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int longestSubsequence(const int *arr, int n) {
    if (n == 0) return 0;

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) return -1; // Add error handling for malloc

    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (abs(arr[i] - arr[j]) == 1) {
                dp[i] = (dp[i] > dp[j] + 1) ? dp[i] : dp[j] + 1;
            }
        }
    }

    int maxLen = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }

    free(dp);
    return maxLen;
}

int main() {
    int arr[] = {10, 9, 4, 5, 4, 8, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longestSubsequence(arr, n);
    printf("The length of the longest subsequence is %d\n", result);
    return 0;
}