#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'X' can be declared as pointer to const [constParameterPointer]
 */
int lrsCount(char *X, int m, int n) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == X[j - 1] && i != j)
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    return dp[m][n];
}

int countLongestRepeatingSubsequence(char *str) {
    int len = strlen(str);
    return lrsCount(str, len, len);
}

int main() {
    char str[] = "AABEBCDD";
    int result = countLongestRepeatingSubsequence(str);
    printf("The length of the longest repeating subsequence is %d\n", result);
    return 0;
}