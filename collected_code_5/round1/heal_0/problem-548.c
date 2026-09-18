#include <stdio.h>

int longestIncreasingSubsequence(int arr[], int n) {
    int i, j, max = 0;
    int dp[n];

    for (i=0; i<n; i++)
        dp[i] = 1;

    for (i=1; i<n; i++)
        for (j=0; j<i; j++)
            if (arr[i]>arr[j] && dp[i]<dp[j]+1)
                dp[i] = dp[j] + 1;
   
    for (i=0; i<n; i++)
        if (max < dp[i])
            max = dp[i];

    return max;
}

int main() {
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The length of the longest increasing subsequence is: %d\n", longestIncreasingSubsequence(arr, n));
    return 0;
}