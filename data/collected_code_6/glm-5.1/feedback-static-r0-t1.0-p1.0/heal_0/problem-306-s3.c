#include <stdio.h>
#include <stdlib.h>

int max_sum_increasing_subsequence(int *arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k >= n || i >= k) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int j = 0; j < n; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j <= i; j++) {
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

    int sum = dp[i] + arr[k];

    free(dp);
    return sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4;
    int k = 6;

    int result = max_sum_increasing_subsequence(arr, n, i, k);
    printf("%d\n", result);

    return 0;
}