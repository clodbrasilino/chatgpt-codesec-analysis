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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t max_len = strnlen(argv[1], SIZE_MAX) + 1;
    int length = longestPalindromicSubsequence(argv[1], max_len);

    printf("%d\n", length);

    return 0;
}