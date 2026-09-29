#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(const char* s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < MAX_STR_LEN && s[len] != '\0') {
        len++;
    }

    if (len == 0 || len == MAX_STR_LEN) {
        return 0;
    }
    
    int n = (int)len;

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
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
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
    const char str[] = "BBABCBCAB";
    int n = longestPalindromicSubsequence(str);
    printf("The length of the longest palindromic subsequence is %d\n", n);
    return 0;
}