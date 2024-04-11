#include <stdio.h>
#include <string.h>

#define MAX_CHAR 26

int longestRepeatedSubSeq(char *str) {
    int n = strlen(str);
    int dp[n+1][n+1];
    memset(dp, 0, sizeof(dp));

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if (str[i-1] == str[j-1] && i != j)
                dp[i][j] =  1 + dp[i-1][j-1];         
            else
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
    }
    return dp[n][n];
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int main() {
    char str[] = "AABEBCDD";
    printf("The length of the largest subsequence that repeats itself is : %d", longestRepeatedSubSeq(str));
    return 0;
}