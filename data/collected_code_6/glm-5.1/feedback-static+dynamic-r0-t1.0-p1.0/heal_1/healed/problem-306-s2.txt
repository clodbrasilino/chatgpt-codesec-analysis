#include <stdio.h>
#include <stdlib.h>

int find_max_sum(const int *arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k >= n || i >= k) {
        return 0;
    }
    
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int j = 0; j <= k; j++) {
        dp[j] = arr[j];
    }

    for (int j = 1; j <= k; j++) {
        for (int m = 0; m < j; m++) {
            if (arr[m] < arr[j]) {
                if (dp[m] + arr[j] > dp[j]) {
                    dp[j] = dp[m] + arr[j];
                }
            }
        }
    }

    int max_sum = 0;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k]) {
            if (dp[j] > max_sum) {
                max_sum = dp[j];
            }
        }
    }

    free(dp);
    return max_sum + arr[k];
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 3;
    int k = 5;
    
    int result = find_max_sum(arr, n, i, k);
    printf("%d\n", result);

    return 0;
}