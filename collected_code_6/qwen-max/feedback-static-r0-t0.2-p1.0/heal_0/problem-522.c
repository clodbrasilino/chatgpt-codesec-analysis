#include <stdio.h>
#include <stdlib.h>

int *lis(int arr[], int n) {
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dp[i] = 1;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
    return dp;
}

int *lds(int arr[], int n) {
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dp[i] = 1;
    for (int i = n - 2; i >= 0; i--)
        for (int j = n - 1; j > i; j--)
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
    return dp;
}

int longestBitonicSubsequence(int arr[], int n) {
    int *inc = lis(arr, n);
    int *dec = lds(arr, n);
    int max_length = 0;
    for (int i = 0; i < n; i++)
        if (max_length < inc[i] + dec[i] - 1)
            max_length = inc[i] + dec[i] - 1;
    free(inc);
    free(dec);
    return max_length;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest bitonic subsequence is %d\n", longestBitonicSubsequence(arr, n));
    return 0;
}