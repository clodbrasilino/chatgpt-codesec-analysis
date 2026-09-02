#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5013, got 6000
  *  test case 2 failed: expected 27, got 10
  *  test case 0 failed: expected 2101, got 1200
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int dp[n];
    dp[0] = arr[0];
    dp[1] = arr[1];
    dp[2] = (dp[0] + arr[2]) > dp[1] ? (dp[0] + arr[2]) : dp[1];

    for (int i = 3; i < n; i++) {
        dp[i] = arr[i] + dp[i-2] > dp[i-1] ? arr[i] + dp[i-2] : dp[i-1];
        dp[i] = arr[i] + dp[i-3] > dp[i] ? arr[i] + dp[i-3] : dp[i];
    }

    return dp[n-1] > dp[n-2] ? dp[n-1] : dp[n-2];
}

int main() {
    int arr[] = {1, 2, 3, 1, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", max_sum_no_three_consecutive(arr, n));
    return 0;
}