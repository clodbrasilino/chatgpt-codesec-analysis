#include <stdio.h>
#include <stdlib.h>

unsigned long long delannoy(int m, int n) {
    if (m < 0 || n < 0) {
        return 0;
    }

    unsigned long long **dp = (unsigned long long **)malloc((m + 1) * sizeof(unsigned long long *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 0; i <= m; i++) {
        dp[i][0] = 1;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + dp[i - 1][j - 1];
        }
    }

    unsigned long long result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

unsigned long long nth_delannoy(int n) {
    return delannoy(n, n);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0) {
        return 1;
    }

    unsigned long long result = nth_delannoy(n);
    printf("%llu\n", result);

    return 0;
}