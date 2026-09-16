#include <stdio.h>
#include <limits.h>

int maxSumSequence(int arr[], int n, int i, int k) {
    int dp[n], max_sum = INT_MIN;
    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }
    for (int j = 0; j < i; j++) {
        if (arr[j] < arr[j+1]) {
            dp[j+1] = dp[j] + arr[j+1];
        }
        if (j == k && dp[j] > max_sum) {
            max_sum = dp[j];
        }
    }
    return max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4, k = 6;
    printf("Maximum sum of increasing subsequence from prefix till %dth index including %dth element: %d\n", i, k, maxSumSequence(arr, n, i, k));
    return 0;
}