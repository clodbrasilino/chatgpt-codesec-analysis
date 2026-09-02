#include <stdio.h>
#include <stdlib.h>

int countSequences(int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(m + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    
    for (int j = 1; j <= m; j++) {
        dp[1][j] = 1;
    }
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= j / 2; k++) {
                dp[i][j] += dp[i-1][k];
            }
        }
    }
    
    int total = 0;
    for (int j = 1; j <= m; j++) {
        total += dp[n][j];
    }
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return total;
}

int main() {
    int n, m;
    
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n <= 0 || m <= 0) {
        fprintf(stderr, "n and m must be positive integers\n");
        return 1;
    }
    
    int result = countSequences(n, m);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Number of possible sequences: %d\n", result);
    
    return 0;
}