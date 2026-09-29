#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char* str, size_t len) {
    if (len == 0) {
        return 0;
    }
    int** dp = (int**)malloc(len * sizeof(int*));
    if (dp == NULL) {
        return -1;
    }
    for (size_t i = 0; i < len; i++) {
        dp[i] = (int*)calloc(len, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        dp[i][i] = 1;
    }
    for (size_t cl = 2; cl <= len; cl++) {
        for (size_t i = 0; i <= len - cl; i++) {
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
    int result = dp[0][len - 1];
    for (size_t i = 0; i < len; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    size_t len = strnlen(argv[1], 1024 * 1024);
    int length = longestPalindromicSubsequence(argv[1], len);
    if (length < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%d\n", length);
    return 0;
}