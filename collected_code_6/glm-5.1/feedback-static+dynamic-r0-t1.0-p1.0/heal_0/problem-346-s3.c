#include <stdio.h>
#include <stdlib.h>

int entringer(int n, int k) {
    if (k < 1 || k > n) {
        return 0;
    }
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((k + 2) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    
    dp[1][1] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i && j <= k; j++) {
            if (j == 1) {
                dp[i][j] = dp[i - 1][i - 1];
            } else {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
            }
        }
    }
    
    int result = dp[n][k];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    int n = 4;
    int k = 2;
    int result = entringer(n, k);
    printf("E(%d, %d) = %d\n", n, k, result);
    return 0;
}