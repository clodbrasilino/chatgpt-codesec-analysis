#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_sequences(int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }
    long long **dp = (long long **)malloc(n * sizeof(long long *));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        dp[i] = (long long *)malloc((m + 1) * sizeof(long long));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = 1;
    }
    for (int i = 1; i < n; i++) {
        long long *prefix_sum = (long long *)malloc((m + 2) * sizeof(long long));
        if (prefix_sum == NULL) {
            for (int j = 0; j < n; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
        prefix_sum[0] = 0;
        for (int j = 1; j <= m + 1; j++) {
            if (prefix_sum[j - 1] > 0 && dp[i - 1][j - 1] > LLONG_MAX - prefix_sum[j - 1]) {
                prefix_sum[j] = LLONG_MAX;
            } else if (prefix_sum[j - 1] < 0 && dp[i - 1][j - 1] < LLONG_MIN - prefix_sum[j - 1]) {
                prefix_sum[j] = LLONG_MIN;
            } else {
                prefix_sum[j] = prefix_sum[j - 1] + dp[i - 1][j - 1];
            }
        }
        for (int j = 1; j <= m; j++) {
            int high = j / 2;
            if (high >= 1) {
                dp[i][j] = prefix_sum[high] - prefix_sum[0];
            } else {
                dp[i][j] = 0;
            }
        }
        free(prefix_sum);
    }
    long long result = 0;
    for (int j = 1; j <= m; j++) {
        if (result > 0 && dp[n - 1][j] > LLONG_MAX - result) {
            result = LLONG_MAX;
        } else if (result < 0 && dp[n - 1][j] < LLONG_MIN - result) {
            result = LLONG_MIN;
        } else {
            result += dp[n - 1][j];
        }
    }
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main() {
    int n = 3;
    int m = 10;
    long long result = count_sequences(n, m);
    printf("%lld\n", result);
    return 0;
}