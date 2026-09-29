#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strnlen(str, 65536);
    if (len == 0) {
        return 0;
    }
    if (len > 65535) {
        return -1;
    }
    int n = (int)len;

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = (int *)calloc((n + 1) * (n + 1), sizeof(int));
    if (dp[0] == NULL) {
        free(dp);
        return -1;
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + (n + 1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[n][n];

    free(dp[0]);
    free(dp);

    return result;
}

int main(void) {
    const char *test1 = "AABEBCDD";
    const char *test2 = "abcabc";
    const char *test3 = "aaaa";
    const char *test4 = "axxxy";

    printf("Longest repeating subsequence of %s: %d\n", test1, longest_repeating_subsequence(test1));
    printf("Longest repeating subsequence of %s: %d\n", test2, longest_repeating_subsequence(test2));
    printf("Longest repeating subsequence of %s: %d\n", test3, longest_repeating_subsequence(test3));
    printf("Longest repeating subsequence of %s: %d\n", test4, longest_repeating_subsequence(test4));

    return 0;
}