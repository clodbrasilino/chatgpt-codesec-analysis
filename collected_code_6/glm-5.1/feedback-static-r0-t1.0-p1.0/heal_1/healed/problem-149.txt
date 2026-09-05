#include <stdio.h>
#include <stdlib.h>

int longest_subsequence(const int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == 1) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }

    int max_len = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 7, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = longest_subsequence(arr, n);

    printf("%d\n", result);

    return 0;
}