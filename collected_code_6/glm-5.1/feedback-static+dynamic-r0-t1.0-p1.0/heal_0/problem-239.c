#include <stdio.h>
#include <stdlib.h>

int count_sequences(int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(m * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int j = 0; j < m; j++) {
        dp[0][j] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = 0;
            int start = (j + 1) / 2;
            for (int k = 0; k < start; k++) {
                dp[i][j] += dp[i - 1][k];
            }
        }
    }

    int result = 0;
    for (int j = 0; j < m; j++) {
        result += dp[n - 1][j];
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n = 4;
    int m = 10;
    int result = count_sequences(n, m);
    printf("%d\n", result);
    return 0;
}