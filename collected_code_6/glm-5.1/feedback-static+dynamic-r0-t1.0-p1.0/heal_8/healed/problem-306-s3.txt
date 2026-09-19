#include <stdio.h>
#include <stdlib.h>

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
            if (arr[j] > arr[l] && dp[l] + arr[j] > dp[j]) {
                dp[j] = dp[l] + arr[j];
            }
        }
    }

    if (arr[k] <= arr[i]) {
        free(dp);
        return 0;
    }

    int max_i = 0;
    int found = 0;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k]) {
            if (!found) {
                max_i = dp[j];
                found = 1;
            } else if (dp[j] > max_i) {
                max_i = dp[j];
            }
        }
    }

    if (!found) {
        free(dp);
        return 0;
    }

    int max_k = 0;
    int found_k = 0;
    for (int j = i + 1; j <= k; j++) {
        if (arr[j] > max_i && arr[j] < arr[k]) {
            if (!found_k) {
                max_k = dp[j];
                found_k = 1;
            } else if (dp[j] > max_k) {
                max_k = dp[j];
            }
        }
    }

    if (!found_k) {
        free(dp);
        return max_i + arr[k];
    }

    free(dp);
    return max_k + arr[k];
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", max_sum_increasing_subsequence(arr, n, 1, 2));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 3, 4));
    printf("%d\n", max_sum_increasing_subsequence(arr, n, 4, 6));

    return 0;
}