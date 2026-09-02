#include <stdio.h>
#include <stdlib.h>

int eulerian(int n, int m) {
    if (m < 0 || m > n - 1 || n < 0) {
        return 0;
    }
    if (n == 0) {
        return (m == 0) ? 1 : 0;
    }
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc((m + 2), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
        if (m >= 1) {
            dp[i][1] = (1 << i) - i - 1;
        }
        for (int j = 2; j <= m && j <= i; j++) {
            dp[i][j] = (i - j) * dp[i - 1][j - 1] + (j + 1) * dp[i - 1][j];
        }
    }
    
    int result = dp[n][m];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    int n = 5;
    int m = 2;
    
    int result = eulerian(n, m);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Eulerian number A(%d, %d) = %d\n", n, m, result);
    
    return 0;
}