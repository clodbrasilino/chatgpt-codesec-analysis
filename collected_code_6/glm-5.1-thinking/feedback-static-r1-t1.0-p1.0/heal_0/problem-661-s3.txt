#include <stdio.h>
#include <stdlib.h>

static inline int max_int(int a, int b) {
    return a > b ? a : b;
}

int max_sum_no_three_consecutive(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = max_int(0, arr[0]);

    if (n >= 2) {
        dp[1] = max_int(0, max_int(arr[0], max_int(arr[1], arr[0] + arr[1])));
    }

    for (int i = 2; i < n; i++) {
        int c1 = dp[i - 1];
        int c2 = dp[i - 2] + arr[i];
        int c3 = (i >= 3 ? dp[i - 3] : 0) + arr[i - 1] + arr[i];
        dp[i] = max_int(0, max_int(c1, max_int(c2, c3)));
    }

    int result = dp[n - 1];
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", result);
    return 0;
}