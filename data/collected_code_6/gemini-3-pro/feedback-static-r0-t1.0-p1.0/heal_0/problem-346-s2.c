#include <stdio.h>
#include <stdlib.h>

long long entringer_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    if (k == 0) {
        return 0;
    }

    long long **dp = (long long **)malloc((n + 1) * sizeof(long long *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (long long *)malloc((n + 1) * sizeof(long long));
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
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
        }
        for (int j = i + 1; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    long long result = dp[n][k];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int n = 5;
    int k = 3;

    long long result = entringer_number(n, k);
    if (result != -1) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}