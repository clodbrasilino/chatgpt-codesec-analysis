#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

char* longest_common_subsequence(const char* X, size_t x_len, const char* Y, size_t y_len) {
    size_t m = x_len;
    size_t n = y_len;

    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    if (dp == NULL) return NULL;
    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return NULL;
        }
    }

    for (size_t i = 0; i <= m; i++) dp[i][0] = 0;
    for (size_t j = 0; j <= n; j++) dp[0][j] = 0;

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    size_t index = dp[m][n];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        for (size_t i = 0; i <= m; i++) free(dp[i]);
        free(dp);
        return NULL;
    }
    lcs[index] = '\0';

    /* Possible weaknesses found:
     *  Shadowed declaration
     */
    size_t i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--index] = X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    /* Possible weaknesses found:
     *  Local variable 'i' shadows outer variable [shadowVariable]
     *  Shadow variable
     */
    for (size_t i = 0; i <= m; i++) free(dp[i]);
    free(dp);

    return lcs;
}

int main() {
    const char* X = "AGGTAB";
    const char* Y = "GXTXAYB";

    char* lcs = longest_common_subsequence(X, strnlen(X, 1024), Y, strnlen(Y, 1024));
    if (lcs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", lcs);
    free(lcs);

    return 0;
}