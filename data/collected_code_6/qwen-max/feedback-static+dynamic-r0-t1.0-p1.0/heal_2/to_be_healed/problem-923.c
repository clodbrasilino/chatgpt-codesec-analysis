#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'str1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'str2' can be declared as pointer to const [constParameterPointer]
 */
int shortestCommonSupersequence(char* str1, char* str2, size_t len1, size_t len2) {
    int dp[len1 + 1][len2 + 1];
    
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
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
    return dp[len1][len2];
}

int main() {
    char str1[] = "AGGTAB";
    char str2[] = "GXTXAYB";
    size_t len1 = sizeof(str1) / sizeof(str1[0]) - 1;
    size_t len2 = sizeof(str2) / sizeof(str2[0]) - 1;
    printf("Length of the shortest common supersequence: %d\n", shortestCommonSupersequence(str1, str2, len1, len2));
    return 0;
}