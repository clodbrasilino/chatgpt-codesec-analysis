#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int maxSumIncreasingSubsequenceWithK(int arr[], int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k < 0 || i >= n || k >= n || k <= i) {
        return INT_MIN;
    }

    int *dp = (int *)malloc((size_t)n * sizeof(int));
    if (dp == NULL) {
        return INT_MIN;
    }

    for (int idx = 0; idx < n; idx++) {
        dp[idx] = arr[idx];
    }

    int maxSum = INT_MIN;

    for (int idx = 1; idx <= i; idx++) {
        for (int prev = 0; prev < idx; prev++) {
            if (arr[idx] > arr[prev] && dp[prev] != INT_MIN) {
                if (dp[idx] < dp[prev] + arr[idx]) {
                    dp[idx] = dp[prev] + arr[idx];
                }
            }
        }
    }

    for (int idx = 0; idx <= i; idx++) {
        if (arr[idx] < arr[k] && dp[idx] != INT_MIN) {
            int currentSum = dp[idx] + arr[k];
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
        }
    }

    free(dp);
    dp = NULL;

    return maxSum;
}

int main(void) {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int i = 4;
    int k = 6;

    int result = maxSumIncreasingSubsequenceWithK(arr, n, i, k);

    if (result != INT_MIN) {
        printf("Maximum sum: %d\n", result);
    } else {
        printf("No valid subsequence found\n");
    }

    return 0;
}