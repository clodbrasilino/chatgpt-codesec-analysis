#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int n = strlen(str);
    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc((n + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    int result = dp[n][n];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    char str[10005];
    if (scanf("%10004s", str) == 1) {
        int length = longestRepeatingSubsequence(str);
        printf("%d\n", length);
    }
    return 0;
}