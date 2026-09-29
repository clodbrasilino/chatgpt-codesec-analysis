#include <stdio.h>
#include <string.h>

int shortestCommonSupersequence(const char* str1, const char* str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int m = (str1 ? strlen(str1) : 0), n = (str2 ? strlen(str2) : 0);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "AGGTAB";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "GXTXAYB";
    printf("Length of the shortest common supersequence: %d\n", shortestCommonSupersequence(str1, str2));
    return 0;
}