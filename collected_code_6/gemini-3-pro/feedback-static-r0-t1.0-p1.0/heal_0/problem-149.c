#include <stdio.h>
#include <stdlib.h>

int longestSubsequenceDiffOne(int arr[], int n) {
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

    int maxLen = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((arr[i] == arr[j] + 1) || (arr[i] == arr[j] - 1)) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (maxLen < dp[i]) {
            maxLen = dp[i];
        }
    }

    free(dp);
    return maxLen;
}

int main() {
    int arr[] = {10, 9, 4, 5, 4, 8, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = longestSubsequenceDiffOne(arr, n);

    printf("%d\n", result);

    return 0;
}