#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int shortestSuperSequence(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int m = strlen(str1);
    int n = strlen(str2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcs = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return m + n - lcs;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";

    int result = shortestSuperSequence(str1, str2);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    return 0;
}