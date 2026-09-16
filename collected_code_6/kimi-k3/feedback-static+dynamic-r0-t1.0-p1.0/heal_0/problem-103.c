#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian(int n, int m) {
    if (m < 0 || m >= n) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (m == 0) {
        return 1;
    }
    if (n == m) {
        return 0;
    }
    
    unsigned long long **dp = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (unsigned long long *)calloc(n + 1, sizeof(unsigned long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][j] = (i - j) * dp[i - 1][j - 1] + (j + 1) * dp[i - 1][j];
        }
    }
    
    unsigned long long result = dp[n][m];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }
    
    if (n < 0 || m < 0) {
        return 1;
    }
    
    printf("%llu\n", eulerian(n, m));
    
    return 0;
}