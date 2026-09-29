#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *s, size_t len) {
    if (len == 0) {
        return 0;
    }

    int *dp = (int *)calloc(len * len, sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        dp[i * len + i] = 1;
    }

    for (size_t cl = 2; cl <= len; cl++) {
        for (size_t i = 0; i <= len - cl; i++) {
            size_t j = i + cl - 1;
            if (s[i] == s[j]) {
                if (cl == 2) {
                    dp[i * len + j] = 2;
                } else {
                    dp[i * len + j] = dp[(i + 1) * len + (j - 1)] + 2;
                }
            } else {
                dp[i * len + j] = max(dp[(i + 1) * len + j], dp[i * len + (j - 1)]);
            }
        }
    }

    int result = dp[0 * len + (len - 1)];
    free(dp);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t len = strlen(argv[1]);
    int length = longestPalindromicSubsequence(argv[1], len);

    printf("%d\n", length);

    return 0;
}