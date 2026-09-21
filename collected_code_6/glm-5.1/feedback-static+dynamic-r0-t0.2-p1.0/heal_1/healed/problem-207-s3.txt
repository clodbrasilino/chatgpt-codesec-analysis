#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubseq(const char *str, size_t len) {
    if (len == 0) {
        return 0;
    }
    int **dp = (int **)malloc((len + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    for (size_t i = 0; i <= len; i++) {
        dp[i] = (int *)malloc((len + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    for (size_t i = 0; i <= len; i++) {
        for (size_t j = 0; j <= len; j++) {
            dp[i][j] = 0;
        }
    }
    for (size_t i = 1; i <= len; i++) {
        for (size_t j = 1; j <= len; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int result = dp[len][len];
    for (size_t i = 0; i <= len; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main() {
    char str1[] = "aabebcdd";
    int res1 = longestRepeatingSubseq(str1, strnlen(str1, sizeof(str1)));
    printf("%d\n", res1);
    char str2[] = "axxxy";
    int res2 = longestRepeatingSubseq(str2, strnlen(str2, sizeof(str2)));
    printf("%d\n", res2);
    char str3[] = "abc";
    int res3 = longestRepeatingSubseq(str3, strnlen(str3, sizeof(str3)));
    printf("%d\n", res3);
    return 0;
}