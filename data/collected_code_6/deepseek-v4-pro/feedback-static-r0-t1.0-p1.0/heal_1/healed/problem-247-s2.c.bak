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
    
    int n = strlen(str);
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
    
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        dp[i][i] = 1;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
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
    *result = (char *)malloc((lpsLength + 1) * sizeof(char));
    if (*result == NULL) {
        for (int i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    int left = 0;
    int right = n - 1;
    char *temp = (char *)malloc((lpsLength + 1) * sizeof(char));
    if (temp == NULL) {
        free(*result);
        *result = NULL;
        for (int i = 0; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return -1;
    }
    
    int leftIndex = 0;
    int rightIndex = lpsLength - 1;
    
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
    strcpy(*result, temp);
    
    free(temp);
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return lpsLength;
}

int main() {
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