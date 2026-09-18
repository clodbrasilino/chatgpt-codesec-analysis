#include <stdio.h>
#include <stdlib.h>

int countSubsequences(int* arr, int n, int k) {
    if (k <= 1 || arr == NULL || n <= 0) {
        return 0;
    }

    int count = 0;
    int dp[k][n + 1];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i < k; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i][j - 1];
            if (arr[j - 1] > 0 && arr[j - 1] <= i) {
                dp[i][j] += dp[i / arr[j - 1]][j - 1] + 1;
            }
        }
    }

    count = dp[k - 1][n];
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 10;

    int result = countSubsequences(arr, n, k);

    printf("%d\n", result);

    return 0;
}