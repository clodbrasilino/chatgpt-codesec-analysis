#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindromicSubsequence(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t n = strlen(str);
    if (n == 0) {
        char* result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }
    
    int** dp = (int**)malloc(n * sizeof(int*));
    if (dp == NULL) {
        return NULL;
    }
    
    for (size_t row = 0; row < n; row++) {
        dp[row] = (int*)calloc(n, sizeof(int));
        if (dp[row] == NULL) {
            for (size_t k = 0; k < row; k++) {
                free(dp[k]);
            }
            free(dp);
            return NULL;
        }
    }
    
    for (size_t diag = 0; diag < n; diag++) {
        dp[diag][diag] = 1;
    }
    
    for (size_t len = 2; len <= n; len++) {
        for (size_t start = 0; start <= n - len; start++) {
            size_t end = start + len - 1;
            if (str[start] == str[end]) {
                dp[start][end] = dp[start + 1][end - 1] + 2;
            } else {
                dp[start][end] = (dp[start + 1][end] > dp[start][end - 1]) ? dp[start + 1][end] : dp[start][end - 1];
            }
        }
    }
    
    int maxLen = dp[0][n - 1];
    char* result = (char*)malloc((size_t)(maxLen + 1) * sizeof(char));
    if (result == NULL) {
        for (size_t row = 0; row < n; row++) {
            free(dp[row]);
        }
        free(dp);
        return NULL;
    }
    
    size_t left = 0, right = n - 1;
    int idx = 0;
    
    while (left <= right) {
        if (left == right) {
            result[idx++] = str[left];
            break;
        }
        if (str[left] == str[right]) {
            result[idx++] = str[left];
            left++;
            right--;
        } else if (dp[left + 1][right] > dp[left][right - 1]) {
            left++;
        } else {
            right--;
        }
    }
    
    for (size_t row = 0; row < n; row++) {
        free(dp[row]);
    }
    free(dp);
    
    result[idx] = '\0';
    return result;
}

int main(void) {
    char input[1024];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    char* result = longestPalindromicSubsequence(input);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Longest palindromic subsequence: %s\n", result);
    printf("Length: %zu\n", strlen(result));
    
    free(result);
    return EXIT_SUCCESS;
}