#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestRepeatingSubseq(const char *s, size_t n) {
    if (s == NULL) {
        return -1;
    }

    int **dp = malloc((n + 1) * sizeof(int *));
    int *vals = malloc((n + 1) * (n + 1) * sizeof(int));
    
    if (dp == NULL || vals == NULL) {
        free(dp);
        free(vals);
        return -1;
    }

    for (size_t i = 0; i <= n; i++) {
        dp[i] = vals + i * (n + 1);
    }

    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[n][n];

    free(vals);
    free(dp);

    return result;
}

int main(void) {
    const char str[] = "AABEBCDD";
    int result = longestRepeatingSubseq(str, sizeof(str) - 1);
    printf("%d\n", result);
    return 0;
}