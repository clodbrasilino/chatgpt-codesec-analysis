#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char* lcs_three(const char *s1, const char *s2, const char *s3) {
    if (s1 == NULL || s2 == NULL || s3 == NULL) {
        return NULL;
    }
    
    size_t len1 = strnlen(s1, SIZE_MAX);
    size_t len2 = strnlen(s2, SIZE_MAX);
    size_t len3 = strnlen(s3, SIZE_MAX);
    
    if (len1 == SIZE_MAX || len2 == SIZE_MAX || len3 == SIZE_MAX) {
        return NULL;
    }
    
    size_t max_len = (len1 > len2) ? len1 : len2;
    max_len = (max_len > len3) ? max_len : len3;
    
    if (max_len > (SIZE_MAX / sizeof(int**)) || max_len > SIZE_MAX - 1) {
        return NULL;
    }
    
    int ***dp = (int***)malloc((len1 + 1) * sizeof(int**));
    if (dp == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i <= len1; i++) {
        dp[i] = NULL;
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
            dp[i][j] = NULL;
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
    if (index == 0) {
        for (size_t row = 0; row <= len1; row++) {
            for (size_t col = 0; col <= len2; col++) {
                free(dp[row][col]);
            }
            free(dp[row]);
        }
        free(dp);
        
        char *empty_result = (char*)malloc(1 * sizeof(char));
        if (empty_result != NULL) {
            empty_result[0] = '\0';
        }
        return empty_result;
    }
    
    char *result = (char*)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        for (size_t row = 0; row <= len1; row++) {
            for (size_t col = 0; col <= len2; col++) {
                free(dp[row][col]);
            }
            free(dp[row]);
        }
        free(dp);
        return NULL;
    }
    result[index] = '\0';
    
    size_t i = len1, j = len2, k = len3;
    size_t temp_index = index;
    while (i > 0 && j > 0 && k > 0 && temp_index > 0) {
        if (s1[i-1] == s2[j-1] && s2[j-1] == s3[k-1]) {
            result[temp_index-1] = s1[i-1];
            temp_index--;
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
    const char str1[] = "ABCBDAB";
    const char str2[] = "BDCABA";
    const char str3[] = "BADBCA";
    
    char *lcs = lcs_three(str1, str2, str3);
    if (lcs != NULL) {
        printf("Longest Common Subsequence: %s\n", lcs);
        printf("Length: %zu\n", strnlen(lcs, SIZE_MAX));
        free(lcs);
    } else {
        printf("Error: Memory allocation failed.\n");
    }
    
    return 0;
}