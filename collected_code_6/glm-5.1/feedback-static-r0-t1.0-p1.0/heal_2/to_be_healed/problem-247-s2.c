#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *s, size_t max_len) {
    size_t n = strnlen(s, max_len);
    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = (int *)calloc(n, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
        dp[i][i] = 1;
    }

    for (size_t cl = 2; cl <= n; cl++) {
        for (size_t i = 0; i <= n - cl; i++) {
            size_t j = i + cl - 1;
            if (s[i] == s[j]) {
                if (cl == 2) {
                    dp[i][j] = 2;
                } else {
                    if (i + 1 <= j - 1) {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    } else {
                        dp[i][j] = 2;
                    }
                }
            } else {
                if (i + 1 <= j) {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                } else {
                    dp[i][j] = 1;
                }
            }
        }
    }

    int result = dp[0][n - 1];

    for (size_t i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = strlen(argv[1]) + 1;
    int length = longestPalindromicSubsequence(argv[1], max_len);

    printf("%d\n", length);

    return 0;
}