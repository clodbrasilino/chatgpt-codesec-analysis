#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memset'
  */

int countSubsequences(int arr[], int n, int k) {
    int dp[n+1][k+1];
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'memset'
     *  implicit declaration of function 'memset' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'memset' [-Wbuiltin-declaration-mismatch]
     */
    memset(dp, 0, sizeof(dp));

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=k; j++) {
            if (arr[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] + dp[i-1][j/arr[i-1]] + 1;
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