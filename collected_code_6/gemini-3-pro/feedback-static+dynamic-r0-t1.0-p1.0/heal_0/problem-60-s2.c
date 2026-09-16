#include <stdio.h>
#include <stdlib.h>

int maxSubsequenceLength(int* arr, int n, int diff) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int* dp = (int*)calloc(n, sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    int maxLength = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] - arr[j] == diff || arr[j] - arr[i] == diff) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    free(dp);
    return maxLength;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int diff = 1;

    int result = maxSubsequenceLength(arr, n, diff);
    printf("Max subsequence length: %d\n", result);

    return 0;
}