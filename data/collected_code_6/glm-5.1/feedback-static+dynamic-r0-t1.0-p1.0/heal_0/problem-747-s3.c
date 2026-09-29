#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

char* lcs_of_3(const char* X, const char* Y, const char* Z) {
    int m = strlen(X);
    int n = strlen(Y);
    int o = strlen(Z);

    int*** dp = (int***)malloc((m + 1) * sizeof(int**));
    if (dp == NULL) return NULL;

    for (int i = 0; i <= m; i++) {
        dp[i] = (int**)malloc((n + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) free(dp[k]);
            free(dp);
            return NULL;
        }
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (int*)malloc((o + 1) * sizeof(int));
            if (dp[i][j] == NULL) {
                for (int k = 0; k <= n; k++) {
                    if (k < j) free(dp[i][k]);
                }
                free(dp[i]);
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l <= n; l++) free(dp[k][l]);
                    free(dp[k]);
                }
                free(dp);
                return NULL;
            }
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    dp[i][j][k] = 0;
                } else if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = max3(dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]);
                }
            }
        }
    }

    int index = dp[m][n][o];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) free(dp[i][j]);
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    lcs[index] = '\0';

    int i = m, j = n, k = o;
    while (i > 0 && j > 0 && k > 0) {
        if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1]) {
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
        for (int b = 0; b <= n; b++) free(dp[a][b]);
        free(dp[a]);
    }
    free(dp);

    return lcs;
}

int main() {
    const char* X = "AGGT12";
    const char* Y = "GXT1X2B";
    const char* Z = "GTT12B";

    char* result = lcs_of_3(X, Y, Z);
    if (result != NULL) {
        printf("Longest Common Subsequence: %s\n", result);
        free(result);
    } else {
        printf("Failed to allocate memory for LCS.\n");
    }

    return 0;
}