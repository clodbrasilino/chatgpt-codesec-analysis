#include <stdio.h>
#include <string.h>

int longestRepeatingSubsequence(const char *str, size_t len) {
    int dp[len+1][len+1];

    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= len; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str[i-1] == str[j-1] && i != j) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }

    return dp[len][len];
}

int main() {
    const char str[] = "AABEBCDD";
    size_t len = sizeof(str) / sizeof(str[0]) - 1;
    printf("Length of the longest repeating subsequence is %d\n", longestRepeatingSubsequence(str, len));
    return 0;
}