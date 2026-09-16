#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m > n) {
        return 0;
    }
    if (m == 0 || m == n) {
        return 1;
    }

    unsigned long long **dp = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (!dp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (unsigned long long *)malloc((m + 1) * sizeof(unsigned long long));
        if (!dp[i]) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j < i) {
                dp[i][j] = ((i - j) * dp[i - 1][j - 1]) + ((j + 1) * dp[i - 1][j]);
            }
        }
    }

    unsigned long long result = dp[n][m];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int n = 5;
    int m = 2;

    unsigned long long result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is %llu\n", n, m, result);

    return EXIT_SUCCESS;
}