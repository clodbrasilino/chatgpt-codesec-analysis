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

    int max_i = dp[i];
    
    int valid = 0;
    for (int l = 0; l < i; l++) {
        if (arr[l] < arr[k]) {
            if (arr[l] < arr[i]) {
                if (dp[l] + arr[i] == dp[i]) {
                    valid = 1;
                    break;
                }
            }
        }
    }

    if (!valid) {
        free(dp);
        return 0;
    }

    int max_mid = 0;
    int found_mid = 0;
    for (int j = i + 1; j < k; j++) {
        if (arr[j] > arr[i] && arr[j] < arr[k]) {
            if (!found_mid) {
                max_mid = dp[j];
                found_mid = 1;
            } else if (dp[j] > max_mid) {
                max_mid = dp[j];
            }
        }
    }

    free(dp);
    
    if (found_mid) {
        return max_mid + arr[k];
    } else {
        return max_i + arr[k];
    }
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", max_sum_increasing_subsequence(arr, n, 1, 2));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 3, 4));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 4, 6));

    return 0;
}