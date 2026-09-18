#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSumNoThreeConsecutive(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return arr[0];
    }
    if (n == 2) {
        return arr[0] + arr[1];
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = max(max(dp[1], arr[1] + arr[2]), arr[0] + arr[2]);

    for (int i = 3; i < n; i++) {
        dp[i] = max(max(dp[i - 1], dp[i - 2] + arr[i]), dp[i - 3] + arr[i] + arr[i - 1]);
    }

    int result = dp[n - 1];
    free(dp);
    return result;
}

int main() {
    int arr[] = {100, 1000, 100, 1000, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxSumNoThreeConsecutive(arr, n);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}