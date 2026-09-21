#include <stdio.h>
#include <string.h>

int longestRepeatingNonOverlappingSubSeq(const char *str, size_t len) {
    if (len == 0) return 0;
    int dp[len+1][len+1];
    
    for (int i = 0; i <= len; i++) {
        dp[i][0] = 0;
        dp[0][i] = 0;
    }
    
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            if (i != j && str[i-1] == str[j-1] && (i < 2 || str[i-1] != str[i-2])) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i][j-1] > dp[i-1][j]) ? dp[i][j-1] : dp[i-1][j];
            }
        }
    }
    
    return dp[len][len];
}

int main() {
    const char str[] = "AABEBCDD";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int result = longestRepeatingNonOverlappingSubSeq(str, len);
    printf("The length of the longest repeating non-overlapping subsequence is %d\n", result);
    return 0;
}