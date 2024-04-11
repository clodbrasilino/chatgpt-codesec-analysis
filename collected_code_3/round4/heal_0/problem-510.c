#include <stdio.h>

int countSubsequences(int arr[], int n, int k) {
    int dp[n+1][k+1];
    memset(dp, 0, sizeof(dp));

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=k; j++) {
            dp[i][j] = dp[i-1][j];
            if (arr[i-1] <= j && arr[i-1] > 0)
                dp[i][j] += dp[i-1][j/arr[i-1]] + 1;
        }
    }
    return dp[n][k];
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int k = 10;
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("%d", countSubsequences(arr, n, k));
    return 0;
}