#include <stdio.h>
#include <string.h>

int longestRepeatingNonOverlappingSubSeq(char *str) {
    int n = strlen(str);
    int dp[n+1][n+1];
    
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[0][i] = 0;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) { // Avoid stack-buffer-underflow by ensuring j > i
            if (str[i-1] == str[j-1] && (i == 1 || str[i-1] != str[i-2])) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i][j-1] > dp[i-1][j]) ? dp[i][j-1] : dp[i-1][j];
            }
        }
    }
    
    return dp[n][n];
}

int main() {
    char str[] = "AABEBCDD";
    int result = longestRepeatingNonOverlappingSubSeq(str);
    printf("The length of the longest repeating non-overlapping subsequence is %d\n", result);
    return 0;
}