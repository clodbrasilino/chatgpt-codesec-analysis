#include <stdio.h>
#include <stdlib.h>

long long find_max_sum_subsequence(const int *arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || k <= i || k >= n) {
        return -1;
    }

    long long *dp = (long long *)malloc((i + 1) * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    long long max_sum = 0;

    for (int j = 0; j <= i; j++) {
        dp[j] = arr[j];
        for (int p = 0; p < j; p++) {
            if (arr[p] < arr[j] && dp[p] + arr[j] > dp[j]) {
                dp[j] = dp[p] + arr[j];
            }
        }
    }

    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k]) {
            if (dp[j] + arr[k] > max_sum) {
                max_sum = dp[j] + arr[k];
            }
        }
    }

    if (max_sum == 0) {
        max_sum = arr[k];
    }

    free(dp);
    return max_sum;
}

int main(void) {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 3;
    int k = 4; 

    long long result = find_max_sum_subsequence(arr, n, i, k);
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }

    return 0;
}