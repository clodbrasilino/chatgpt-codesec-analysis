#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortest_supersequence(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t m = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str2);
    size_t total_elements = (m + 1) * (n + 1);

    int *dp_block = (int *)malloc(total_elements * sizeof(int));
    if (dp_block == NULL) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        free(dp_block);
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i] = dp_block + i * (n + 1);
    }

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] > dp[i][j - 1] ? dp[i][j - 1] : dp[i - 1][j]);
            }
        }
    }

    int result = dp[m][n];
    free(dp);
    free(dp_block);
    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "AGGTAB";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "GXTXAYB";
    int result = shortest_supersequence(str1, str2);
    printf("%d\n", result);
    return 0;
}