#include <stdio.h>
#include <stdlib.h>

int count_sequences(int n, int m) {
    if (n <= 0) {
        return 0;
    }
    if (m <= 0) {
        return 0;
    }

    int *dp = (int *)malloc((m + 1) * sizeof(int));
    if (dp == NULL) {
        exit(1);
    }

    int *next_dp = (int *)malloc((m + 1) * sizeof(int));
    if (next_dp == NULL) {
        free(dp);
        exit(1);
    }

    for (int i = 1; i <= m; ++i) {
        dp[i] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            next_dp[j] = 0;
        }
        for (int j = 1; j <= m; ++j) {
            int start = 2 * j;
            if (start > m) {
                continue;
            }
            for (int k = start; k <= m; ++k) {
                next_dp[k] += dp[j];
            }
        }
        for (int j = 1; j <= m; ++j) {
            dp[j] = next_dp[j];
        }
    }

    int total = 0;
    for (int i = 1; i <= m; ++i) {
        total += dp[i];
    }

    free(dp);
    free(next_dp);

    return total;
}

int main() {
    int n = 4;
    int m = 10;
    int result = count_sequences(n, m);
    printf("%d\n", result);
    return 0;
}