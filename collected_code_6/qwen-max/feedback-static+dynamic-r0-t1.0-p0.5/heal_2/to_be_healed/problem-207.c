#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int longestRepeatingSubsequence(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    int dp[n+1][n+1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str[i-1] == str[j-1] && i != j) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }

    return dp[n][n];
}

int main() {
    const char str[] = "AABEBCDD";
    printf("Length of the longest repeating subsequence is %d\n", longestRepeatingSubsequence(str));
    return 0;
}