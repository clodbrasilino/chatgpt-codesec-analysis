#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char *s, size_t max_len) {
    if (s == NULL) {
        return 0;
    }

    size_t n = 0;
    while (n < max_len && s[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        dp[i] = (int *)calloc(n, sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (size_t i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (size_t cl = 2; cl <= n; cl++) {
        for (size_t i = 0; i < n - cl + 1; i++) {
            size_t j = i + cl - 1;
            if (s[i] == s[j] && cl == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
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

int main(void) {
    const char s[] = "bbbab";
    size_t max_len = sizeof(s);
    int length = longestPalindromicSubsequence(s, max_len);
    
    if (length != -1) {
        printf("%d\n", length);
    } else {
        printf("Memory allocation failed.\n");
        return 1;
    }

    return 0;
}