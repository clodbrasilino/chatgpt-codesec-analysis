#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int enitringer(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((i + 1) * sizeof(int));
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
        dp[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
        }
    }
    int result = dp[n][k];
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return 1;
    }
    int n = (int)val1;
    
    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return 1;
    }
    int k = (int)val2;
    
    if (n < 0 || k < 0 || k > n) {
        return 1;
    }
    int result = enitringer(n, k);
    printf("%d\n", result);
    return 0;
}