#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max3(int a, int b, int c) {
    int max = a > b ? a : b;
    return max > c ? max : c;
}

char* lcs_three(char* s1, char* s2, char* s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) return NULL;
    
    int len1 = (int)strnlen(s1, 65536);
    int len2 = (int)strnlen(s2, 65536);
    int len3 = (int)strnlen(s3, 65536);
    
    int*** dp = (int***)malloc((len1 + 1) * sizeof(int**));
    if (dp == NULL) return NULL;
    
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int**)malloc((len2 + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (int x = 0; x < i; x++) {
                for (int y = 0; y <= len2; y++) {
                    free(dp[x][y]);
                }
                free(dp[x]);
            }
            free(dp);
            return NULL;
        }
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = (int*)calloc(len3 + 1, sizeof(int));
            if (dp[i][j] == NULL) {
                for (int y = 0; y < j; y++) {
                    free(dp[i][y]);
                }
                free(dp[i]);
                for (int x = 0; x < i; x++) {
                    for (int y = 0; y <= len2; y++) {
                        free(dp[x][y]);
                    }
                    free(dp[x]);
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
    
    int i2 = len1, j2 = len2, k2 = len3;
    int index = lcs_len;
    result[index] = '\0';
    
    while (i2 > 0 && j2 > 0 && k2 > 0) {
        if (s1[i2-1] == s2[j2-1] && s2[j2-1] == s3[k2-1]) {
            result[--index] = s1[i2-1];
            i2--; j2--; k2--;
        } else if (dp[i2-1][j2][k2] >= dp[i2][j2-1][k2] && dp[i2-1][j2][k2] >= dp[i2][j2][k2-1]) {
            i2--;
        } else if (dp[i2][j2-1][k2] >= dp[i2-1][j2][k2] && dp[i2][j2-1][k2] >= dp[i2][j2][k2-1]) {
            j2--;
        } else {
            k2--;
        }
    }
    
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
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
        printf("Length: %zu\n", strnlen(result, 65536));
        free(result);
    } else {
        printf("No common subsequence found\n");
    }
    
    return 0;
}