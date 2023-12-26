#include <stdio.h>
#include <string.h>

int longestRepeatingSubsequence(char *str){
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int n = strlen(str);
    int dp[n+1][n+1];
    
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;
            }
            else if(str[i-1] == str[j-1] && i != j){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = dp[i][j-1] > dp[i-1][j] ? dp[i][j-1] : dp[i-1][j];
            }
        }
    }
    
    return dp[n][n];
}

int main(){
    char str[] = "aabebcdd";
    int longest = longestRepeatingSubsequence(str);
    
    printf("Longest repeating subsequence count: %d\n", longest);
    
    return 0;
}