#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int shortestSupersequenceLength(const char *str1, const char *str2) {
    size_t m, n, dp_size, i, j;
    int *dp_block;
    int **dp;
    int lcs_len;

    if (!str1 || !str2) {
        return -1;
    }

    m = strlen(str1);
    n = strlen(str2);

    /* Possible weaknesses found:
     *  Assuming that condition 'm==0' is not redundant
     */
    if (m == 0) return (int)n;
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     *  Assuming condition is false
     */
    if (n == 0) return (int)m;

    /* Possible weaknesses found:
     *  Condition '(n+1)==0' is always false
     *  Condition '(m+1)==0' is always false
     *  Condition '(n+1)==0' is always false [knownConditionTrueFalse]
     *  Condition '(m+1)==0' is always false [knownConditionTrueFalse]
     */
    if ((n + 1) == 0 || (m + 1) == 0 || (m + 1) > SIZE_MAX / (n + 1)) {
        return -1;
    }
    dp_size = (m + 1) * (n + 1);

    if (dp_size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    if ((m + 1) > SIZE_MAX / sizeof(int *)) {
        return -1;
    }

    dp_block = (int *)malloc(dp_size * sizeof(int));
    if (!dp_block) {
        return -1;
    }

    dp = (int **)malloc((m + 1) * sizeof(int *));
    if (!dp) {
        free(dp_block);
        return -1;
    }

    for (i = 0; i <= m; i++) {
        dp[i] = dp_block + i * (n + 1);
    }

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    lcs_len = dp[m][n];

    free(dp);
    free(dp_block);

    return (int)(m + n - (size_t)lcs_len);
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    int result;

    result = shortestSupersequenceLength(str1, str2);
    printf("%d\n", result);

    return 0;
}