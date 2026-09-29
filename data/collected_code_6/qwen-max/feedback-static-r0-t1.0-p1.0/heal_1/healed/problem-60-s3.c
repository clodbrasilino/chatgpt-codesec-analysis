#include <stdio.h>
#include <stdlib.h>

int max_length_subsequence(const int *arr, int n, int d) {
    int *dp = (int *)calloc(n, sizeof(int));
    int maxLength = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] - arr[j] == d && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                if (dp[i] > maxLength) {
                    maxLength = dp[i];
                }
            }
        }
    }
    
    free(dp);
    return maxLength + 1;
}

int main() {
    int arr[] = {1, 5, 7, 8, 5, 3, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int d = 2;
    
    printf("Maximum length of subsequence: %d\n", max_length_subsequence(arr, n, d));
    
    return 0;
}