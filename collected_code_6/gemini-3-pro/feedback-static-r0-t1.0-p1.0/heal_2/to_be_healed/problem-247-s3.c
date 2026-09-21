#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_STR_LEN 100000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t n = 0;
    /* Possible weaknesses found:
     *  Array index 'n' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[n] != '\0' && n < MAX_STR_LEN) {
        n++;
    }

    if (n == 0 || n == MAX_STR_LEN) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
        for (size_t j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (size_t i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (size_t cl = 2; cl <= n; cl++) {
        for (size_t i = 0; i < n - cl + 1; i++) {
            size_t j = i + cl - 1;
            if (str[i] == str[j] && cl == 2) {
                dp[i][j] = 2;
            } else if (str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }

    int lps = dp[0][n - 1];

    for (size_t i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return lps;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "BBABCBCAB";
    int length = longestPalindromicSubsequence(str);
    printf("%d\n", length);
    return 0;
}