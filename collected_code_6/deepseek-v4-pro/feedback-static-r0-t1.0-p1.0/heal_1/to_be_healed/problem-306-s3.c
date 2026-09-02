#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int maxSumIncreasingSubsequenceWithK(int arr[], int n, int k, int i) {
    if (i < 0 || i >= n || k < 0 || k >= n || k <= i) {
        return INT_MIN;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (!dp) {
        return INT_MIN;
    }

    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j <= i; j++) {
        for (int l = 0; l < j; l++) {
            if (arr[l] < arr[j] && dp[l] + arr[j] > dp[j]) {
                dp[j] = dp[l] + arr[j];
            }
        }
    }

    int maxPrefix = INT_MIN;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k] && dp[j] > maxPrefix) {
            maxPrefix = dp[j];
        }
    }

    if (maxPrefix == INT_MIN) {
        free(dp);
        return INT_MIN;
    }

    int result = maxPrefix + arr[k];
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4;
    int k = 6;

    int result = maxSumIncreasingSubsequenceWithK(arr, n, k, i);
    
    if (result != INT_MIN) {
        printf("%d\n", result);
    } else {
        printf("No valid subsequence exists\n");
    }

    return 0;
}