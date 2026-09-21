#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_subsequence(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s2);

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

    size_t lcs_len = (size_t)dp[m][n];
    char *lcs = (char *)malloc(lcs_len + 1);
    if (lcs == NULL) {
        for (size_t i = 0; i <= m; i++) free(dp[i]);
        free(dp);
        return NULL;
    }
    lcs[lcs_len] = '\0';

    size_t i = m, j = n, index = lcs_len;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[--index] = s1[i - 1];
            i--;
            j--;
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