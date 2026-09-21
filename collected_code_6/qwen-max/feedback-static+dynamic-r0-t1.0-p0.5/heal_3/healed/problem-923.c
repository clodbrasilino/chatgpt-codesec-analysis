#include <stdio.h>
#include <stddef.h>
#include <string.h>

int shortestCommonSupersequenceLength(const char *str1, size_t len1, const char *str2, size_t len2) {
    int dp[len1 + 1][len2 + 1];

    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = i + j;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }

    return dp[len1][len2];
}

int main() {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";

    size_t len1 = sizeof(str1) - 1;
    size_t len2 = sizeof(str2) - 1;

    int result = shortestCommonSupersequenceLength(str1, len1, str2, len2);
    printf("Length of the shortest common supersequence: %d\n", result);

    return 0;
}