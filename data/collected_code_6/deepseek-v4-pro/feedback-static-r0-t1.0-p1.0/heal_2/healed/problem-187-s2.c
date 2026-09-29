#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_subsequence(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return NULL;

    size_t m = strnlen(s1, 4096);
    size_t n = strnlen(s2, 4096);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) return NULL;

    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return NULL;
        }
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int lcs_len = dp[m][n];
    if (lcs_len == 0) {
        for (size_t i = 0; i <= m; i++) free(dp[i]);
        free(dp);
        char *empty = (char *)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    char *lcs = (char *)malloc((size_t)lcs_len + 1);
    if (lcs == NULL) {
        for (size_t i = 0; i <= m; i++) free(dp[i]);
        free(dp);
        return NULL;
    }

    lcs[lcs_len] = '\0';
    size_t i = m, j = n;
    int index = lcs_len - 1;

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[index] = s1[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (size_t k = 0; k <= m; k++) free(dp[k]);
    free(dp);
    return lcs;
}

int main(void) {
    const char *s1 = "ABCBDAB";
    const char *s2 = "BDCABB";
    char *lcs = longest_common_subsequence(s1, s2);
    if (lcs != NULL) {
        printf("%s\n", lcs);
        free(lcs);
    }
    return 0;
}