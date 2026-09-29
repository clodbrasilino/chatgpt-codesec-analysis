#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

int longestRepeatingSubsequences(char *str);

/* Possible weaknesses found:
 *  declared here
 */
int min(int x, int y, int z) {
    /* Possible weaknesses found:
     *  too few arguments to function 'min'
     */
    return min(min(x, y), z);
}

int main() {
    char str[] = "aabb";
    printf("The length of the largest subsequence that repeats itself is: %d\n",
           longestRepeatingSubsequences(str));
    return 0;
}

int longestRepeatingSubsequences(char *str) {
    int n = strlen(str);
    int dp[n + 1][n + 1][MAX_CHAR];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k < MAX_CHAR; k++)
                dp[i][j][k] = 0;
  
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j)
                /* Possible weaknesses found:
                 *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
                 */
                dp[i][j][str[i - 1]] = max(dp[i][j][str[i - 1]],
                                       dp[i - 1][j - 1][str[i - 1]] + 1);
            else
                for (int k = 0; k < MAX_CHAR; k++)
                    dp[i][j][k] = max(dp[i][j][k],
                                  max(dp[i][j - 1][k], dp[i - 1][j][k]));
        }
    }
  
    int result = 0;
    for (int k = 0; k < MAX_CHAR; k++)
        result = max(result, dp[n][n][k]);
    return result;
}