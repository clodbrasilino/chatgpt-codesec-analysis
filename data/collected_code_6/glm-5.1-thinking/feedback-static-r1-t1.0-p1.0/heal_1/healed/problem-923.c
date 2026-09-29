#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortestSupersequenceLength(const char *str1, size_t len1, const char *str2, size_t len2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t m = len1;
    size_t n = len2;

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = (int)j;
            } else if (j == 0) {
                dp[i][j] = (int)i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }

    int result = dp[m][n];

    for (size_t i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *str1 = "abac";
    const char *str2 = "cab";
    size_t len1 = sizeof("abac") - 1;
    size_t len2 = sizeof("cab") - 1;
    int result = shortestSupersequenceLength(str1, len1, str2, len2);
    printf("%d\n", result);
    return 0;
}