#include <stdio.h>
#include <stdlib.h>

int longestSubsequence(const int *arr, int n) {
    if (n == 0) return 0;
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] - arr[j] == 1 || arr[i] - arr[j] == -1) {
                dp[i] = (dp[i] > dp[j] + 1) ? dp[i] : dp[j] + 1;
            }
        }
    }
    int max_length = dp[0];
    for (int i = 1; i < n; ++i) {
        if (dp[i] > max_length) {
            max_length = dp[i];
        }
    }
    free(dp);
    return max_length;
}

int main() {
    int arr[] = {10, 9, 4, 5, 4, 8, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longestSubsequence(arr, n);
    printf("Length of the longest subsequence where difference between adjacents is one: %d\n", result);
    return 0;
}