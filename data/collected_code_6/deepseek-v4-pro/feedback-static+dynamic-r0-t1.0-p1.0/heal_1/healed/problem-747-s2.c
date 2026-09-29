#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* lcs_three(const char *s1, const char *s2, const char *s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) {
        return NULL;
    }
    
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);
    
    int ***dp = (int***)malloc((len1 + 1) * sizeof(int**));
    if (dp == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i <= len1; i++) {
        dp[i] = (int**)malloc((len2 + 1) * sizeof(int*));
        if (dp[i] == NULL) {
            for (size_t ii = 0; ii < i; ii++) {
                for (size_t jj = 0; jj <= len2; jj++) {
                    free(dp[ii][jj]);
                }
                free(dp[ii]);
            }
            free(dp);
            return NULL;
        }
        for (size_t j = 0; j <= len2; j++) {
            dp[i][j] = (int*)calloc(len3 + 1, sizeof(int));
            if (dp[i][j] == NULL) {
                for (size_t jj = 0; jj < j; jj++) {
                    free(dp[i][jj]);
                }
                for (size_t ii = 0; ii < i; ii++) {
                    for (size_t jj = 0; jj <= len2; jj++) {
                        free(dp[ii][jj]);
                    }
                    free(dp[ii]);
                }
                free(dp[i]);
                free(dp);
                return NULL;
            }
        }
    }
    
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            for (size_t k = 1; k <= len3; k++) {
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
    
    size_t index = dp[len1][len2][len3];
    char *result = (char*)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        for (size_t i = 0; i <= len1; i++) {
            for (size_t j = 0; j <= len2; j++) {
                free(dp[i][j]);
            }
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    result[index] = '\0';
    
    size_t i = len1, j = len2, k = len3;
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
    
    for (size_t row = 0; row <= len1; row++) {
        for (size_t col = 0; col <= len2; col++) {
            free(dp[row][col]);
        }
        free(dp[row]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    char str1[] = "ABCBDAB";
    char str2[] = "BDCABA";
    char str3[] = "BADBCA";
    
    char *lcs = lcs_three(str1, str2, str3);
    if (lcs != NULL) {
        printf("Longest Common Subsequence: %s\n", lcs);
        printf("Length: %zu\n", strlen(lcs));
        free(lcs);
    } else {
        printf("Error: Memory allocation failed.\n");
    }
    
    return 0;
}