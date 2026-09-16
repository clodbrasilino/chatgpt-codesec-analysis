#include <stdio.h>
#include <stdlib.h>

long long entringer(int n, int k) {
    if (n == 0 && k == 0) {
        return 1;
    }
    if (k == 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    
    long long **dp = (long long **)malloc((n + 1) * sizeof(long long *));
    if (!dp) {
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long *)malloc((n + 1) * sizeof(long long));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    dp[0][0] = 1;

    for (int j = 1; j <= n; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
        }
    }

    long long result = 0;
    if (k <= n) {
        result = dp[n][k];
    }

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }

    if (n < 0 || k < 0 || k > n) {
        return 1;
    }

    long long result = entringer(n, k);
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        return 1;
    }

    return 0;
}