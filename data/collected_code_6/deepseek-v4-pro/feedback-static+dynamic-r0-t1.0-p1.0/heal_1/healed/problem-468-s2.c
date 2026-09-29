#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProductIncreasingSubsequence(const int arr[], int n) {
    if (n <= 0) return 0;
    
    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL) return 0;
    
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }
    
    int maxProduct = dp[0];
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                int candidate = dp[j] * arr[i];
                if (candidate > dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
        if (dp[i] > maxProduct) {
            maxProduct = dp[i];
        }
    }
    
    free(dp);
    return maxProduct;
}

int main() {
    int arr1[] = {3, 2, 6, 4, 5, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", maxProductIncreasingSubsequence(arr1, n1));
    
    int arr2[] = {-3, -2, -1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", maxProductIncreasingSubsequence(arr2, n2));
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", maxProductIncreasingSubsequence(arr3, n3));
    
    int arr4[] = {5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", maxProductIncreasingSubsequence(arr4, n4));
    
    int arr5[] = {2, 1, 3, 2, 4};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", maxProductIncreasingSubsequence(arr5, n5));
    
    return 0;
}