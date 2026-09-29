#include <stdio.h>
#include <stdlib.h>

int maxLengthSubsequence(const int *arr, int n, int diff) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    int *dp = (int *)malloc((size_t)n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    int maxLen = 1;
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (abs(arr[i] - arr[j]) == diff && dp[j] + 1 > dp[i]) {
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

int main(void) {
    int arr[] = {1, 5, 3, 4, 2, 6};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int diff = 2;
    
    int result = maxLengthSubsequence(arr, n, diff);
    printf("%d\n", result);
    
    return 0;
}