#include <stdio.h>
#include <stdlib.h>

int maxIncreasingSubsequenceSum(int* arr, int n) {
    if (n <= 0) {
        return 0;
    }
    
    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[i] < dp[j] + arr[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
    }
    
    int max_sum = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }
    
    free(dp);
    return max_sum;
}

int main() {
    int arr1[] = {1, 101, 2, 3, 100, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", maxIncreasingSubsequenceSum(arr1, n1));
    
    int arr2[] = {3, 2, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[1]);
    printf("%d\n", maxIncreasingSubsequenceSum(arr2, n2));
    
    return 0;
}