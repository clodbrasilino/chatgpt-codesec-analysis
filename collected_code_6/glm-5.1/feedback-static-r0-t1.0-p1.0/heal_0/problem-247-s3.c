#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *str) {
    int n = strlen(str);
    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int *)calloc(n, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
        dp[i][i] = 1;
    }

    for (int cl = 2; cl <= n; cl++) {
        for (int i = 0; i <= n - cl; i++) {
            int j = i + cl - 1;
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

    int result = dp[0][n - 1];

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    const char *str1 = "bbbab";
    int len1 = longestPalindromicSubsequence(str1);
    printf("%d\n", len1);

    const char *str2 = "cbbd";
    int len2 = longestPalindromicSubsequence(str2);
    printf("%d\n", len2);

    const char *str3 = "";
    int len3 = longestPalindromicSubsequence(str3);
    printf("%d\n", len3);

    return 0;
}