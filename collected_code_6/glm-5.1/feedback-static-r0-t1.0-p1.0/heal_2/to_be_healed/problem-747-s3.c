#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

char* lcs_of_3(const char* X, const char* Y, const char* Z, size_t x_len, size_t y_len, size_t z_len) {
    size_t m = x_len;
    size_t n = y_len;
    size_t o = z_len;

    int*** dp = (int***)malloc((m + 1) * sizeof(int**));
    if (dp == NULL) return NULL;

    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int**)malloc((n + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (size_t k = 0; k < i; k++) free(dp[k]);
            free(dp);
            return NULL;
        }
        for (size_t j = 0; j <= n; j++) {
            dp[i][j] = (int*)malloc((o + 1) * sizeof(int));
            if (dp[i][j] == NULL) {
                for (size_t k = 0; k < j; k++) free(dp[i][k]);
                free(dp[i]);
                for (size_t k = 0; k < i; k++) {
                    for (size_t l = 0; l <= n; l++) free(dp[k][l]);
                    free(dp[k]);
                }
                free(dp);
                return NULL;
            }
        }
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            for (size_t k = 0; k <= o; k++) {
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

    size_t index = dp[m][n][o];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        for (size_t i = 0; i <= m; i++) {
            for (size_t j = 0; j <= n; j++) free(dp[i][j]);
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    lcs[index] = '\0';

    size_t i = m, j = n, k = o;
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

    for (size_t a = 0; a <= m; a++) {
        for (size_t b = 0; b <= n; b++) free(dp[a][b]);
        free(dp[a]);
    }
    free(dp);

    return lcs;
}

int main() {
    const char* X = "AGGT12";
    const char* Y = "GXT1X2B";
    const char* Z = "GTT12B";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char* result = lcs_of_3(X, Y, Z, strlen(X), strlen(Y), strlen(Z));
    if (result != NULL) {
        printf("Longest Common Subsequence: %s\n", result);
        free(result);
    } else {
        printf("Failed to allocate memory for LCS.\n");
    }

    return 0;
}