#include <stdio.h>
#include <stdlib.h>

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int dp[n];
    dp[0] = arr[0];
    dp[1] = arr[0] > arr[1] ? arr[0] : arr[1];
    dp[2] = arr[2] + ((dp[0] > dp[1]) ? dp[0] : dp[1]);

    for (int i = 3; i < n; i++) {
        dp[i] = arr[i] + ((dp[i-2] > dp[i-3]) ? dp[i-2] : dp[i-3]);
    }

    int max_sum = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }

    return max_sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = max_sum_no_three_consecutive(arr, n);
    printf("%d\n", result);

    int arr1[] = {1, 20, 3};
    n = sizeof(arr1) / sizeof(arr1[0]);
    result = max_sum_no_three_consecutive(arr1, n);
    printf("%d\n", result);

    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    n = sizeof(arr2) / sizeof(arr2[0]);
    result = max_sum_no_three_consecutive(arr2, n);
    printf("%d\n", result);

    return 0;
}