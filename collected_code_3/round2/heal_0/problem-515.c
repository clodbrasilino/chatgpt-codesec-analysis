#include <stdio.h>
#include <stdbool.h>

bool checkSubset(int arr[], int n, int m) {
    if (m == 0)
        return true;
    if (n == 0 && m != 0)
        return false;

    bool dp[n+1][m];
    for (int i=0; i<=n; i++)
        dp[i][0] = true;

    for (int i=1; i<=m; i++)
        dp[0][i] = false;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= arr[i-1])
                dp[i][j] |= dp[i-1][j-arr[i-1]];
        }
    }
    return dp[n][m];
}

int main() {
    int arr[] = {3, 1, 7, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int m = 6;

    if (checkSubset(arr, n, m) == true)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}