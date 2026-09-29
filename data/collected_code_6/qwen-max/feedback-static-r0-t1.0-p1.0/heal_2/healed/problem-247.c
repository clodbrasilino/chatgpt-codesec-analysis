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

int longestPalindromicSubsequence(const char *seq, size_t len) {
    int **dp = createLPSMatrix(len);
    for (int sublen = 1; sublen <= (int)len; sublen++) {
        for (int i = 0; i + sublen - 1 < (int)len; i++) {
            int j = i + sublen - 1;
            lps(seq, i, j, dp);
        }
    }
    int result = dp[0][(int)len-1];
    freeLPSMatrix(dp, (int)len);
    return result;
}

int main() {
    const char seq[] = "BBABCBCAB";
    size_t len = strlen(seq);
    printf("The length of the longest palindromic subsequence is %d\n", longestPalindromicSubsequence(seq, len));
    return 0;
}