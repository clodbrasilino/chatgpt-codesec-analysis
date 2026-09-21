#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(char *str, char **result) {
    if (str == NULL || result == NULL) {
        return -1;
    }
    
    size_t n = strnlen(str, 65536);
    if (n == 0) {
        *result = (char *)malloc(1);
        if (*result == NULL) {
            return -1;
        }
        (*result)[0] = '\0';
        return 0;
    }
    
    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        dp[i][i] = 1;
    }
    
    for (size_t len = 2; len <= n; len++) {
        for (size_t i = 0; i < n - len + 1; i++) {
            size_t j = i + len - 1;
            if (str[i] == str[j] && len == 2) {
                dp[i][j] = 2;
            } else if (str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    
    int lpsLength = dp[0][n - 1];
    
    if (lpsLength < 0) {
        for (size_t i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    size_t allocSize = (size_t)lpsLength + 1;
    
    if (allocSize == 0 || (int)allocSize - 1 != lpsLength) {
        for (size_t i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    *result = (char *)malloc(allocSize);
    if (*result == NULL) {
        for (size_t i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    size_t left = 0;
    size_t right = n - 1;
    char *temp = (char *)malloc(allocSize);
    if (temp == NULL) {
        free(*result);
        *result = NULL;
        for (size_t i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    size_t leftIndex = 0;
    size_t rightIndex = (size_t)lpsLength - 1;
    
    while (left <= right) {
        if (str[left] == str[right]) {
            temp[leftIndex++] = str[left];
            if (leftIndex <= rightIndex) {
                temp[rightIndex--] = str[right];
            }
            left++;
            right--;
        } else if (dp[left + 1][right] > dp[left][right - 1]) {
            left++;
        } else {
            right--;
        }
    }
    
    temp[lpsLength] = '\0';
    
    size_t tempLen = strnlen(temp, allocSize);
    if (tempLen >= allocSize) {
        free(temp);
        free(*result);
        *result = NULL;
        for (size_t i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    size_t lenToCopy = tempLen + 1;
    if (lenToCopy > allocSize) {
        lenToCopy = allocSize;
    }
    
    memcpy(*result, temp, lenToCopy);
    (*result)[allocSize - 1] = '\0';
    
    free(temp);
    for (size_t i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return lpsLength;
}

int main(void) {
    char str[] = "character";
    char *result = NULL;
    
    int length = longestPalindromicSubsequence(str, &result);
    if (length == -1) {
        printf("Error processing string\n");
        return 1;
    }
    
    printf("Input string: %s\n", str);
    printf("Longest palindromic subsequence length: %d\n", length);
    printf("Longest palindromic subsequence: %s\n", result);
    
    free(result);
    return 0;
}