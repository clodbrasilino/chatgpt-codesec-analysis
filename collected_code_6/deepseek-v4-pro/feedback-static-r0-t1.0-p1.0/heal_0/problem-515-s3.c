#include <stdio.h>
#include <stdbool.h>

bool hasSubsetSumDivisibleByM(int arr[], int n, int m) {
    if (n == 0 || m <= 0) {
        return false;
    }
    
    bool dp[1000];
    for (int i = 0; i < m; i++) {
        dp[i] = false;
    }
    dp[0] = true;
    
    for (int i = 0; i < n; i++) {
        bool temp[1000];
        for (int j = 0; j < m; j++) {
            temp[j] = dp[j];
        }
        
        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                int new_rem = (j + arr[i] % m + m) % m;
                temp[new_rem] = true;
            }
        }
        
        for (int j = 0; j < m; j++) {
            dp[j] = temp[j];
        }
    }
    
    return dp[0];
}

int main(void) {
    int arr[] = {3, 1, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 6;
    
    if (hasSubsetSumDivisibleByM(arr, n, m)) {
        printf("Subset with sum divisible by %d exists.\n", m);
    } else {
        printf("No subset with sum divisible by %d exists.\n", m);
    }
    
    return 0;
}