#include <stdio.h>
#include <limits.h>

int maxSumIncreasingSubsequence(int arr[], int n, int i, int k) {
    int dp[n];
    for (int j = 0; j < n; ++j) {
        dp[j] = 0;
    }
    dp[i] = arr[i];

    for (int j = i + 1; j < k; ++j) {
        if (arr[j] > arr[i]) {
            dp[j] = arr[j] + dp[i];
            for (int l = i + 1; l < j; ++l) {
                if (arr[l] < arr[j] && arr[l] > arr[i]) {
                    dp[j] = (dp[j] > (arr[j] + dp[l])) ? dp[j] : (arr[j] + dp[l]);
                }
            }
        }
    }

    int max_sum = INT_MIN;
    for (int j = i + 1; j <= k; ++j) {
        if (arr[j] > arr[i]) {
            max_sum = (max_sum > dp[j]) ? max_sum : dp[j];
        }
    }

    return max_sum == INT_MIN ? 0 : max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 0;
    int k = 4;
    printf("Maximum sum of increasing subsequence: %d\n", maxSumIncreasingSubsequence(arr, n, i, k));
    return 0;
}