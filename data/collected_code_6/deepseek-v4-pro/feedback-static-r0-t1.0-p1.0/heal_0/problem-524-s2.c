#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_max_increasing_subsequence(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    int max_sum = arr[0];
    
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + arr[i]) {
                dp[i] = dp[j] + arr[i];
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
    int result = sum_max_increasing_subsequence(arr, n);
    
    printf("%d\n", result);
    
    int arr2[] = {3, 4, 5, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = sum_max_increasing_subsequence(arr2, n2);
    
    printf("%d\n", result2);
    
    int arr3[] = {10, 5, 4, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = sum_max_increasing_subsequence(arr3, n3);
    
    printf("%d\n", result3);
    
    return 0;
}