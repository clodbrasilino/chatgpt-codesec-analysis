#include <stdio.h>
#include <stdlib.h>

int longestSubsequenceWithDiffOne(int arr[], int n) {
    if (n == 0) return 0;

    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int maxLength = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] - arr[j] == 1 || arr[j] - arr[i] == 1) {
                dp[i] = (dp[i] > dp[j] + 1) ? dp[i] : dp[j] + 1;
                if (dp[i] > maxLength) {
                    maxLength = dp[i];
                }
            }
        }
    }

    return maxLength;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest subsequence: %d\n", longestSubsequenceWithDiffOne(arr, n));
    return 0;
}