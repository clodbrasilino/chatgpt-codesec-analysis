#include <stdio.h>
#include <stdlib.h>

int entringer(int n, int k) {
    if (n == 0 && k == 0) {
        return 1;
    }
    if (k == 0) {
        return 0;
    }
    if (k > n) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc((i + 2), sizeof(int));
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
        dp[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            if (j == i) {
                dp[i][j] = dp[i][0];
            } else {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][i - j];
            }
        }
    }

    int result = dp[n][k];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int n, k;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading n\n");
        return 1;
    }

    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Error reading k\n");
        return 1;
    }

    if (n < 0 || k < 0) {
        fprintf(stderr, "n and k must be non-negative\n");
        return 1;
    }

    int result = entringer(n, k);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("E(%d, %d) = %d\n", n, k, result);

    return 0;
}