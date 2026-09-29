#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long delannoy(int n, int m) {
    if (n < 0 || m < 0) {
        return -1;
    }
    
    long long **dp = (long long **)malloc((n + 1) * sizeof(long long *));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long *)malloc((m + 1) * sizeof(long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1];
            }
        }
    }
    
    long long result = dp[n][m];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

long long nth_delannoy(int n) {
    return delannoy(n, n);
}

int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[1] || val < 0 || val > 1000) {
        printf("Invalid input: please provide a non-negative integer\n");
        return 1;
    }
    
    n = (int)val;
    
    long long result = nth_delannoy(n);
    if (result == -1) {
        printf("Error: could not compute Delannoy number\n");
        return 1;
    }
    
    printf("D(%d, %d) = %lld\n", n, n, result);
    
    return 0;
}