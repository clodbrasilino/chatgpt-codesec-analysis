#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max3(int a, int b, int c) {
    int m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    return m;
}

char* longest_common_subsequence_3(const char *X, const char *Y, const char *Z) {
    int m = strlen(X);
    int n = strlen(Y);
    int o = strlen(Z);

    int ***dp = (int ***)malloc((m + 1) * sizeof(int **));
    dp[0] = (int **)malloc((m + 1) * (n + 1) * sizeof(int *));
    for (int i = 1; i <= m; i++) {
        dp[i] = (int **)malloc((n + 1) * sizeof(int *));
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (int *)malloc((o + 1) * sizeof(int));
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    dp[i][j][k] = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = max3(
                        dp[i - 1][j][k],
                        dp[i][j - 1][k],
                        dp[i][j][k - 1]
                    );
                }
            }
        }
    }

    int index = dp[m][n][o];
    if (index == 0) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                free(dp[i][j]);
            }
            free(dp[i]);
        }
        free(dp);
        char *empty = (char *)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    int i = m, j = n, k = o;
    while (i > 0 && j > 0 && k > 0) {
        if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            k--;
            index--;
        } else if (dp[i - 1][j][k] >= dp[i][j - 1][k] && dp[i - 1][j][k] >= dp[i][j][k - 1]) {
            i--;
        } else if (dp[i][j - 1][k] >= dp[i - 1][j][k] && dp[i][j - 1][k] >= dp[i][j][k - 1]) {
            j--;
        } else {
            k--;
        }
    }

    for (int a = 0; a <= m; a++) {
        for (int b = 0; b <= n; b++) {
            free(dp[a][b]);
        }
        free(dp[a]);
    }
    free(dp);

    return lcs;
}

int main(void) {
    const char *X = "AGGT12";
    const char *Y = "GXTXAYBK12";
    const char *Z = "GGTX11B12";

    char *result = longest_common_subsequence_3(X, Y, Z);

    printf("%s\n", result);

    free(result);

    return 0;
}