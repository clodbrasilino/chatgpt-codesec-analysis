#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || n == 0) {
        if (n == 0 && m == 0) {
            return 1;
        }
        return 0;
    }
    
    if (m >= n) {
        return 0;
    }
    
    unsigned long long **dp = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (unsigned long long *)calloc((i + 1), sizeof(unsigned long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (j == 0) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = (i - j) * dp[i-1][j-1] + (j + 1) * dp[i-1][j];
            }
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
    
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    
    unsigned long long result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) = %llu\n", n, m, result);
    
    return 0;
}