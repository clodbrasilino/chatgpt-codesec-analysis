#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max3(int a, int b, int c) {
    int max = a > b ? a : b;
    return max > c ? max : c;
}

char* lcs_three(char* s1, char* s2, char* s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) return NULL;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    
    int*** dp = (int***)malloc((len1 + 1) * sizeof(int**));
    if (dp == NULL) return NULL;
    
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int**)malloc((len2 + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (int m = 0; m < i; m++) {
                for (int n = 0; n <= len2; n++) {
                    free(dp[m][n]);
                }
                free(dp[m]);
            }
            free(dp);
            return NULL;
        }
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = (int*)calloc(len3 + 1, sizeof(int));
            if (dp[i][j] == NULL) {
                for (int n = 0; n < j; n++) {
                    free(dp[i][n]);
                }
                free(dp[i]);
                for (int m = 0; m < i; m++) {
                    for (int n = 0; n <= len2; n++) {
                        free(dp[m][n]);
                    }
                    free(dp[m]);
                }
                free(dp);
                return NULL;
            }
        }
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            for (int k = 1; k <= len3; k++) {
                if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                } else {
                    dp[i][j][k] = max3(dp[i-1][j][k], dp[i][j-1][k], dp[i][j][k-1]);
                }
            }
        }
    }
    
    int lcs_len = dp[len1][len2][len3];
    char* result = (char*)malloc((lcs_len + 1) * sizeof(char));
    if (result == NULL) {
        for (int i = 0; i <= len1; i++) {
            for (int j = 0; j <= len2; j++) {
                free(dp[i][j]);
            }
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    
    int i = len1;
    int j = len2;
    int k = len3;
    int index = lcs_len;
    result[index] = '\0';
    
    while (i > 0 && j > 0 && k > 0) {
        if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
            result[--index] = s1[i-1];
            i--; j--; k--;
        } else if (dp[i-1][j][k] >= dp[i][j-1][k] && dp[i-1][j][k] >= dp[i][j][k-1]) {
            i--;
        } else if (dp[i][j-1][k] >= dp[i-1][j][k] && dp[i][j-1][k] >= dp[i][j][k-1]) {
            j--;
        } else {
            k--;
        }
    }
    
    for (int row = 0; row <= len1; row++) {
        for (int col = 0; col <= len2; col++) {
            free(dp[row][col]);
        }
        free(dp[row]);
    }
    free(dp);
    
    return result;
}

int main() {
    char s1[] = "ABCDEF";
    char s2[] = "ACDEF";
    char s3[] = "ABDF";
    
    char* result = lcs_three(s1, s2, s3);
    
    if (result != NULL) {
        printf("LCS of three strings: %s\n", result);
        printf("Length: %zu\n", strlen(result));
        free(result);
    } else {
        printf("No common subsequence found\n");
    }
    
    return 0;
}