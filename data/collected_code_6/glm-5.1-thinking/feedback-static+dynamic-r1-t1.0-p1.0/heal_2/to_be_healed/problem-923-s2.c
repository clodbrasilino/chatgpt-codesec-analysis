#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int shortestSupersequenceLength(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str2);

    if (m == SIZE_MAX || n == SIZE_MAX) {
        return -1;
    }

    if (m == 0) return (int)n;
    if (n == 0) return (int)m;

    if (m + 1 > SIZE_MAX / (n + 1)) {
        return -1;
    }

    size_t dp_size = (m + 1) * (n + 1);

    if (dp_size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    if (m + 1 > SIZE_MAX / sizeof(int *)) {
        return -1;
    }

    int *dp_block = (int *)malloc(dp_size * sizeof(int));
    if (!dp_block) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (!dp) {
        free(dp_block);
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i] = dp_block + i * (n + 1);
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int lcs_len = dp[m][n];

    free(dp);
    free(dp_block);

    if (m > SIZE_MAX - n) {
        return -1;
    }

    size_t scs_len = m + n - (size_t)lcs_len;

    if (scs_len > INT_MAX) {
        return -1;
    }

    return (int)scs_len;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    int result;

    result = shortestSupersequenceLength(str1, str2);
    printf("%d\n", result);

    return 0;
}