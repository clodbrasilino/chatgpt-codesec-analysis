#include <stdio.h>
#include <stdlib.h>

int count_sequences(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        dp[i][1] = i;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if (i / 2 >= 1) {
                dp[i][j] += dp[i / 2][j - 1];
            }
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int m = 10;
    int n = 4;
    int result = count_sequences(m, n);
    printf("%d\n", result);
    return 0;
}