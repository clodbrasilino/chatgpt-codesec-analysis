#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maxSubsequenceLength(const int *arr, int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) return -1;
    
    int maxLen = 1;
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == 1 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }
    
    free(dp);
    return maxLen;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Max length: %d\n", maxSubsequenceLength(arr1, n1));

    int arr2[] = {1, 3, 2, 4, 6, 5, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Max length: %d\n", maxSubsequenceLength(arr2, n2));

    int arr3[] = {10, 20, 30};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Max length: %d\n", maxSubsequenceLength(arr3, n3));

    int arr4[] = {5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Max length: %d\n", maxSubsequenceLength(arr4, n4));

    int arr5[] = {};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("Max length: %d\n", maxSubsequenceLength(arr5, n5));

    return 0;
}