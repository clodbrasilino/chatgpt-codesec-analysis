#include <stdio.h>
#include <stdlib.h>

int longestSubsequence(int* arr, int n) {
    if (n == 0) {
        return 0;
    }
    
    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == 1) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }
    
    int max_len = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    
    free(dp);
    return max_len;
}

int main() {
    int arr1[] = {1, 2, 3, 2, 3, 7, 2, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = longestSubsequence(arr1, n1);
    printf("%d\n", result1);

    int arr2[] = {10, 9, 4, 5, 4, 8, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = longestSubsequence(arr2, n2);
    printf("%d\n", result2);
    
    int arr3[] = {};
    int n3 = 0;
    int result3 = longestSubsequence(arr3, n3);
    printf("%d\n", result3);

    return 0;
}