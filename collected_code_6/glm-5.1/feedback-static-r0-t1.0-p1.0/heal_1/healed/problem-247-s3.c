#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *str, size_t str_len) {
    if (str_len == 0) {
        return 0;
    }

    int **dp = (int **)malloc(str_len * sizeof(int *));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < str_len; i++) {
        dp[i] = (int *)calloc(str_len, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
        dp[i][i] = 1;
    }

    for (size_t cl = 2; cl <= str_len; cl++) {
        for (size_t i = 0; i <= str_len - cl; i++) {
            size_t j = i + cl - 1;
            if (str[i] == str[j]) {
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

    int result = dp[0][str_len - 1];

    for (size_t i = 0; i < str_len; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    const char *str1 = "bbbab";
    int len1 = longestPalindromicSubsequence(str1, strnlen(str1, SIZE_MAX));
    printf("%d\n", len1);

    const char *str2 = "cbbd";
    int len2 = longestPalindromicSubsequence(str2, strnlen(str2, SIZE_MAX));
    printf("%d\n", len2);

    const char *str3 = "";
    int len3 = longestPalindromicSubsequence(str3, strnlen(str3, SIZE_MAX));
    printf("%d\n", len3);

    return 0;
}