#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    if (len == max_len) return 0;
    return len;
}

static size_t max_size_t(size_t a, size_t b) {
    return (a > b) ? a : b;
}

char* longest_common_subsequence(const char* X, const char* Y) {
    size_t m = safe_strlen(X, 1024 * 1024);
    size_t n = safe_strlen(Y, 1024 * 1024);

    size_t** dp = (size_t**)malloc((m + 1) * sizeof(size_t*));
    if (dp == NULL) return NULL;
    for (size_t i = 0; i <= m; i++) {
        dp[i] = (size_t*)malloc((n + 1) * sizeof(size_t));
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
                dp[i][j] = max_size_t(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    size_t index = dp[m][n];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    if (lcs == NULL) {
        for (size_t k = 0; k <= m; k++) free(dp[k]);
        free(dp);
        return NULL;
    }
    lcs[index] = '\0';

    size_t row = m, col = n;
    while (row > 0 && col > 0) {
        if (X[row - 1] == Y[col - 1]) {
            lcs[--index] = X[row - 1];
            row--;
            col--;
        } else if (dp[row - 1][col] > dp[row][col - 1]) {
            row--;
        } else {
            col--;
        }
    }

    for (size_t k = 0; k <= m; k++) free(dp[k]);
    free(dp);

    return lcs;
}

int main() {
    const char* X = "AGGTAB";
    const char* Y = "GXTXAYB";

    char* lcs = longest_common_subsequence(X, Y);
    if (lcs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", lcs);
    free(lcs);

    return 0;
}