#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_subsequence(const char *s1, const char *s2) {
    int m = (int)strlen(s1);
    int n = (int)strlen(s2);
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) return NULL;
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return NULL;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    int lcs_len = dp[m][n];
    char *lcs = (char *)malloc((lcs_len + 1) * sizeof(char));
    if (lcs == NULL) {
        for (int i = 0; i <= m; i++) free(dp[i]);
        free(dp);
        return NULL;
    }
    lcs[lcs_len] = '\0';
    int i = m, j = n, index = lcs_len - 1;
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
    for (int k = 0; k <= m; k++) free(dp[k]);
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