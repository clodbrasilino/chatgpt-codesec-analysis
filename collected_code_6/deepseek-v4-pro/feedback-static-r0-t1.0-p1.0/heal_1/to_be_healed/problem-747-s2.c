#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* lcs_three(char *s1, char *s2, char *s3) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    
    int ***dp = (int***)malloc((len1 + 1) * sizeof(int**));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int**)malloc((len2 + 1) * sizeof(int*));
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = (int*)calloc(len3 + 1, sizeof(int));
        }
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            for (int k = 1; k <= len3; k++) {
                if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                } else {
                    int max = dp[i-1][j][k];
                    if (dp[i][j-1][k] > max) max = dp[i][j-1][k];
                    if (dp[i][j][k-1] > max) max = dp[i][j][k-1];
                    dp[i][j][k] = max;
                }
            }
        }
    }
    
    int index = dp[len1][len2][len3];
    char *result = (char*)malloc((index + 1) * sizeof(char));
    result[index] = '\0';
    
    /* Possible weaknesses found:
     *  Shadowed declaration
     */
    int i = len1, j = len2, k = len3;
    while (i > 0 && j > 0 && k > 0) {
        if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
            result[index-1] = s1[i-1];
            index--;
            i--; j--; k--;
        } else if (dp[i-1][j][k] >= dp[i][j-1][k] && dp[i-1][j][k] >= dp[i][j][k-1]) {
            i--;
        } else if (dp[i][j-1][k] >= dp[i-1][j][k] && dp[i][j-1][k] >= dp[i][j][k-1]) {
            j--;
        } else {
            k--;
        }
    }
    
    /* Possible weaknesses found:
     *  Local variable 'i' shadows outer variable [shadowVariable]
     *  Shadow variable
     */
    for (int i = 0; i <= len1; i++) {
        /* Possible weaknesses found:
         *  Shadow variable
         *  Local variable 'j' shadows outer variable [shadowVariable]
         */
        for (int j = 0; j <= len2; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    char str1[] = "ABCBDAB";
    char str2[] = "BDCABA";
    char str3[] = "BADBCA";
    
    char *lcs = lcs_three(str1, str2, str3);
    printf("Longest Common Subsequence: %s\n", lcs);
    printf("Length: %zu\n", strlen(lcs));
    
    free(lcs);
    return 0;
}