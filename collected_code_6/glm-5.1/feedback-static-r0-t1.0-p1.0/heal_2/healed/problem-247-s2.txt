#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *s, size_t max_len) {
    size_t n = strnlen(s, max_len);
    if (n == 0) {
        return 0;
    }

    int *dp_mem = (int *)calloc(n * n, sizeof(int));
    if (dp_mem == NULL) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        free(dp_mem);
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = dp_mem + i * n;
        dp[i][i] = 1;
    }

    for (size_t cl = 2; cl <= n; cl++) {
        for (size_t i = 0; i <= n - cl; i++) {
            size_t j = i + cl - 1;
            if (s[i] == s[j]) {
                if (cl == 2) {
                    dp[i][j] = 2;
                } else {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    int result = dp[0][n - 1];

    free(dp);
    free(dp_mem);

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t max_len = strnlen(argv[1], SIZE_MAX) + 1;
    int length = longestPalindromicSubsequence(argv[1], max_len);

    printf("%d\n", length);

    return 0;
}