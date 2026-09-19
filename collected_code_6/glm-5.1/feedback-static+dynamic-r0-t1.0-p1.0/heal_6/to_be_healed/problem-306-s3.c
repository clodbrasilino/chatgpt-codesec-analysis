#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 11, got 6
  *  test case 2 failed: expected 71, got 45
  *  test case 1 failed: expected 7, got 0
  */

int max_sum_increasing_subsequence(const int *arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k < 0 || i >= k || k >= n) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j < n; j++) {
        for (int l = 0; l < j; l++) {
            if (arr[j] > arr[l]) {
                if (dp[l] + arr[j] > dp[j]) {
                    dp[j] = dp[l] + arr[j];
                }
            }
        }
    }

    if (arr[k] <= arr[i]) {
        free(dp);
        return 0;
    }

    int max_i = 0;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k] && dp[j] > max_i) {
            max_i = dp[j];
        }
    }

    free(dp);
    return max_i + arr[k];
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", max_sum_increasing_subsequence(arr, n, 1, 2));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 3, 4));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 4, 6));

    return 0;
}