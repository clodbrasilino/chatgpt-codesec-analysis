#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int arr[], int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0] > 0 ? arr[0] : 0;
    if (n == 2) {
        int sum = arr[0] + arr[1];
        return sum > 0 ? sum : 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) return 0;

    dp[0] = arr[0] > 0 ? arr[0] : 0;
    dp[1] = (arr[0] + arr[1]) > 0 ? (arr[0] + arr[1]) : 0;
    dp[2] = (arr[0] + arr[1]) > (arr[1] + arr[2]) ? (arr[0] + arr[1]) : (arr[1] + arr[2]);
    dp[2] = dp[2] > arr[0] ? dp[2] : arr[0];
    dp[2] = dp[2] > arr[2] ? dp[2] : arr[2];
    if (dp[2] < 0) dp[2] = 0;

    for (int i = 3; i < n; i++) {
        int val1 = dp[i - 1];
        int val2 = dp[i - 2] + arr[i];
        int val3 = dp[i - 3] + arr[i - 1] + arr[i];
        
        dp[i] = val1 > val2 ? val1 : val2;
        dp[i] = dp[i] > val3 ? dp[i] : val3;
    }

    int result = dp[n - 1];
    free(dp);
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_sum = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", max_sum);
    return 0;
}