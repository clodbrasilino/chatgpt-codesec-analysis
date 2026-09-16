#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_palindromic_subsequence(const char *str) {
    int n = strlen(str);
    unsigned short **dp = malloc(n * sizeof(*dp));
    if (!dp) return NULL;
    for (int i = 0; i < n; i++) {
        dp[i] = calloc(n, sizeof(**dp));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return NULL;
        }
    }

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (str[i] == str[j] && len == 2)
                dp[i][j] = 2;
            else if (str[i] == str[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1]) ? dp[i + 1][j] : dp[i][j - 1];
        }
    }

    int len = dp[0][n - 1];
    char *result = malloc(len + 1);
    if (!result) {
        for (int i = 0; i < n; i++) free(dp[i]);
        free(dp);
        return NULL;
    }

    int i = 0, j = n - 1, pos = 0, rev = len - 1;
    while (i <= j) {
        if (str[i] == str[j]) {
            result[pos++] = str[i];
            if (i != j) result[rev--] = str[j];
            i++;
            j--;
        } else if (dp[i + 1][j] > dp[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }
    result[len] = '\0';

    for (int k = 0; k < n; k++) free(dp[k]);
    free(dp);

    return result;
}

int main(void) {
    const char *tests[] = {
        "character",
        "civic",
        "babad",
        "forgeeksskeegfor",
        "bbabcbcab",
        ""
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int t = 0; t < num_tests; t++) {
        char *lps = longest_palindromic_subsequence(tests[t]);
        if (lps) {
            printf("Input: \"%s\"\nLongest palindromic subsequence: \"%s\"\n\n", tests[t], lps);
            free(lps);
        } else {
            printf("Input: \"%s\"\nMemory allocation failed or empty string.\n\n", tests[t]);
        }
    }

    return 0;
}