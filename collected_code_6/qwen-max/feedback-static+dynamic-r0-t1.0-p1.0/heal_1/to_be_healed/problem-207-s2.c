#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'X' can be declared as pointer to const [constParameterPointer]
 */
int longestRepeatingSubsequence(char *X, int m, int n) {
    int dp[m+1][n+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i-1] == X[j-1] && i != j) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    return dp[m][n];
}

int main() {
    char str[] = "AABEBCDD";
    int len = strlen(str);
    printf("Length of LRS is %d", longestRepeatingSubsequence(str, len, len));
    return 0;
}