#include <stdio.h>
#include <stdlib.h>

int max_sum_increasing_subsequence(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    int max_sum = dp[0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (dp[j] + arr[i] > dp[i]) {
                    dp[i] = dp[j] + arr[i];
                }
            }
        }
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }

    free(dp);
    return max_sum;
}

int main(void) {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", max_sum_increasing_subsequence(arr, n));

    return 0;
}