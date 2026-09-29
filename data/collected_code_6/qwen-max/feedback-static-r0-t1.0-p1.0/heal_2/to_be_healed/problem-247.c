#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int **createLPSMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
    }
    return matrix;
}

void freeLPSMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int lps(const char *seq, int i, int j, int **dp) {
    if (i == j) {
        dp[i][j] = 1;
    } else if (seq[i] == seq[j] && i + 1 == j) {
        dp[i][j] = 2;
    } else if (seq[i] == seq[j]) {
        dp[i][j] = dp[i+1][j-1] + 2;
    } else {
        dp[i][j] = (dp[i+1][j] > dp[i][j-1]) ? dp[i+1][j] : dp[i][j-1];
    }
    return dp[i][j];
}

/* Possible weaknesses found:
 *  Shadowed declaration
 */
int longestPalindromicSubsequence(const char *seq, size_t len) {
    int **dp = createLPSMatrix(len);
    /* Possible weaknesses found:
     *  Local variable 'len' shadows outer argument [shadowArgument]
     *  Shadow variable
     */
    for (int len = 1; len <= (int)len; len++) {
        for (int i = 0; i + len - 1 < (int)len; i++) {
            int j = i + len - 1;
            lps(seq, i, j, dp);
        }
    }
    int result = dp[0][(int)len-1];
    freeLPSMatrix(dp, (int)len);
    return result;
}

int main() {
    const char seq[] = "BBABCBCAB";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(seq);
    printf("The length of the longest palindromic subsequence is %d\n", longestPalindromicSubsequence(seq, len));
    return 0;
}