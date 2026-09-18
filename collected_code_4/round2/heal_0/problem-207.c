#include <stdio.h>
#include <string.h>
#define MAX 1000
  
int dp[MAX][MAX];
  
int max(int a, int b) {
    return (a > b) ? a : b;
}
  
int longestRepeatingSubsequence(char *str) {
    int n = strlen(str);
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
  
int main() {
    char str[] = "aab";
    printf("The length of longest repeating subsequence is %d",
            longestRepeatingSubsequence(str));
    return 0;
}