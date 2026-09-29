#include <stdio.h>
#include <stdlib.h>

int max_length_subsequence(int *arr, int n, int diff) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    int max_len = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == diff) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int diff = 1;

    int result = max_length_subsequence(arr, n, diff);
    printf("%d\n", result);

    return 0;
}