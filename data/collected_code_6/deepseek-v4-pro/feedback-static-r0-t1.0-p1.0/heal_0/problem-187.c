#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_subsequence(const char *seq1, const char *seq2) {
    int len1 = (int)strlen(seq1);
    int len2 = (int)strlen(seq2);
    int **dp;
    int i, j, index;
    char *result;

    dp = (int **)malloc((len1 + 1) * sizeof(int *));
    if (dp == NULL) {
        return NULL;
    }

    for (i = 0; i <= len1; i++) {
        dp[i] = (int *)calloc(len2 + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }

    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    index = dp[len1][len2];
    result = (char *)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        for (i = 0; i <= len1; i++) {
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    result[index] = '\0';

    i = len1;
    j = len2;
    while (i > 0 && j > 0) {
        if (seq1[i - 1] == seq2[j - 1]) {
            result[--index] = seq1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *seq1 = "ABCBDAB";
    const char *seq2 = "BDCABB";
    char *lcs = longest_common_subsequence(seq1, seq2);

    if (lcs != NULL) {
        printf("%s\n", lcs);
        free(lcs);
    }

    return 0;
}