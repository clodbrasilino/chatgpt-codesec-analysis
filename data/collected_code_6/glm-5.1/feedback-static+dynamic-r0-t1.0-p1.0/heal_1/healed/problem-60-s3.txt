#include <stdio.h>
#include <stdlib.h>

int max_subseq_len(const int *arr, int n, int k) {
    if (n == 0) {
        return 0;
    }
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    int max_len = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) <= k && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    free(dp);
    dp = NULL;
    return max_len;
}

int main() {
    int arr[] = {1, 3, 2, 4, 5, 7, 6, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 1;
    int result = max_subseq_len(arr, n, k);
    printf("%d\n", result);
    return 0;
}