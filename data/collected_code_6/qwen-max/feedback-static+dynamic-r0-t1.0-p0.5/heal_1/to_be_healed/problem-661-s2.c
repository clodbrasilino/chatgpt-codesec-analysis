#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 27, got 10
  *  test case 0 failed: expected 2101, got 1200
  *  test case 1 failed: expected 5013, got 6000
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int dp[n];
    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = (arr[0] > arr[1]) ? (arr[0] + arr[2]) : (arr[1] + arr[2]);

    for (int i = 3; i < n; i++) {
        dp[i] = arr[i] + ((dp[i-2] > dp[i-3]) ? dp[i-2] : dp[i-3]);
    }

    return (dp[n-1] > dp[n-2]) ? dp[n-1] : dp[n-2];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", result);
    return 0;
}