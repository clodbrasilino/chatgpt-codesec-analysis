#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

int shortestCommonSupersequenceLength(const char *str1, const char *str2, size_t len1, size_t len2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }
    
    if (len1 == 0) {
        if (len2 > INT32_MAX) {
            return -1;
        }
        return (int)len2;
    }
    if (len2 == 0) {
        if (len1 > INT32_MAX) {
            return -1;
        }
        return (int)len1;
    }
    
    if (len1 > SIZE_MAX - 1 || len2 > SIZE_MAX - 1) {
        return -1;
    }
    
    if ((len1 + 1) > SIZE_MAX / sizeof(int *) || (len2 + 1) > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    int **dp = malloc((len1 + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i <= len1; i++) {
        dp[i] = malloc((len2 + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    
    for (size_t i = 0; i <= len1; i++) {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j <= len2; j++) {
        dp[0][j] = 0;
    }
    
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    int lcsLength = dp[len1][len2];
    
    if (len1 > SIZE_MAX - len2) {
        for (size_t i = 0; i <= len1; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    size_t totalLen = len1 + len2;
    if (totalLen > INT32_MAX || (size_t)lcsLength > totalLen) {
        for (size_t i = 0; i <= len1; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    int result = (int)totalLen - lcsLength;
    
    for (size_t i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";
    
    size_t len1 = strnlen(str1, sizeof(str1));
    size_t len2 = strnlen(str2, sizeof(str2));
    
    if (len1 == sizeof(str1) || len2 == sizeof(str2)) {
        fprintf(stderr, "Error: String not null-terminated within expected bounds\n");
        return 1;
    }
    
    int result = shortestCommonSupersequenceLength(str1, str2, len1, len2);
    
    if (result >= 0) {
        printf("Length of shortest common supersequence: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input or memory allocation failure\n");
        return 1;
    }
    
    return 0;
}