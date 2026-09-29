#include <stdio.h>

int longestSubsequence(int arr[], int n) {
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    int max_len = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((arr[i] == arr[j] + 1) || (arr[i] == arr[j] - 1)) {
                dp[i] = dp[j] + 1;
                if (dp[i] > max_len) {
                    max_len = dp[i];
                }
            }
        }
    }
    return max_len;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 7, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest subsequence is %d\n", longestSubsequence(arr, n));
    return 0;
}