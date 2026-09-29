#include <stdio.h>
#include <string.h>

int longestRepeatingSubsequence(const char *str, size_t str_len) {
    int dp[str_len+1][str_len+1];
    
    for (int i = 0; i <= str_len; i++) {
        for (int j = 0; j <= str_len; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str[i-1] == str[j-1] && i != j) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    return dp[str_len][str_len];
}

int main() {
    const char str[] = "AABEBCDD";
    printf("Length of the longest repeating subsequence is %d\n", longestRepeatingSubsequence(str, sizeof(str)/sizeof(char) - 1));
    return 0;
}