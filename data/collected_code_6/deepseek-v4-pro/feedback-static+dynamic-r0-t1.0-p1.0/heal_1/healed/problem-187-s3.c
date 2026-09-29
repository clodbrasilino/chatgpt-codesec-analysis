#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_subsequence(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    size_t m = strlen(s1);
    size_t n = strlen(s2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return NULL;
    }

    dp[0] = (int *)calloc((m + 1) * (n + 1), sizeof(int));
    if (dp[0] == NULL) {
        free(dp);
        return NULL;
    }

    for (size_t i = 1; i <= m; i++) {
        dp[i] = dp[0] + i * (n + 1);
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

    int lcs_length = dp[m][n];
    char *lcs = (char *)malloc((size_t)(lcs_length + 1) * sizeof(char));
    if (lcs == NULL) {
        free(dp[0]);
        free(dp);
        return NULL;
    }
    lcs[lcs_length] = '\0';

    size_t i = m, j = n;
    int index = lcs_length;
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

    free(dp[0]);
    free(dp);

    return lcs;
}

int main(void) {
    const char *seq1 = "AGGTAB";
    const char *seq2 = "GXTXAYB";

    char *result = longest_common_subsequence(seq1, seq2);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("LCS: %s\n", result);
    free(result);

    return 0;
}