#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[n][n];

    for (size_t i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *test1 = "AABEBCDD";
    const char *test2 = "abcabc";
    const char *test3 = "aaaa";
    const char *test4 = "axxxy";

    printf("%d\n", longest_repeating_subsequence(test1));
    printf("%d\n", longest_repeating_subsequence(test2));
    printf("%d\n", longest_repeating_subsequence(test3));
    printf("%d\n", longest_repeating_subsequence(test4));

    return 0;
}