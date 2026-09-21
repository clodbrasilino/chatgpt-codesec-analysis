#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) return 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char* s, size_t max_allowed_len) {
    if (s == NULL) {
        return 0;
    }

    size_t n_size = safe_strlen(s, max_allowed_len);
    if (n_size == 0) {
        return 0;
    }

    int n = (int)n_size;

    int** dp = (int**)malloc(n * sizeof(int*));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int*)calloc(n, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
        dp[i][i] = 1;
    }

    for (int cl = 2; cl <= n; cl++) {
        for (int i = 0; i < n - cl + 1; i++) {
            int j = i + cl - 1;
            if (s[i] == s[j] && cl == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max_val(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }

    int lps = dp[0][n - 1];

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return lps;
}

int main(void) {
    char str[] = "BBABCBCAB";
    int n = longestPalindromicSubsequence(str, 4096);
    printf("The length of the longest palindromic subsequence is %d\n", n);
    return 0;
}