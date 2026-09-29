#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int longestRepeatingSubsequence(const char *str, size_t max_len) {
    if (str == NULL) {
        return -1;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    
    if (len > (SIZE_MAX - 1) / (len + 1) || 
        (len + 1) * (len + 1) > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    int *dp = calloc((len + 1) * (len + 1), sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    int maxLen = 0;
    
    for (size_t i = 1; i <= len; i++) {
        for (size_t j = 1; j <= len; j++) {
            size_t idx = i * (len + 1) + j;
            size_t prevDiag = (i - 1) * (len + 1) + (j - 1);
            size_t prevUp = (i - 1) * (len + 1) + j;
            size_t prevLeft = i * (len + 1) + (j - 1);
            
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[idx] = dp[prevDiag] + 1;
            } else {
                dp[idx] = (dp[prevUp] > dp[prevLeft]) ? dp[prevUp] : dp[prevLeft];
            }
            
            if (dp[idx] > maxLen) {
                maxLen = dp[idx];
            }
        }
    }
    
    free(dp);
    return maxLen;
}

int main(void) {
    const char *test1 = "aabb";
    const char *test2 = "aab";
    const char *test3 = "aabebcdd";
    const char *test4 = "";
    const size_t max_input_len = 1024;
    
    int result;
    
    result = longestRepeatingSubsequence(test1, max_input_len);
    if (result >= 0) {
        printf("Input: \"%s\" -> Longest Repeating Subsequence: %d\n", test1, result);
    }
    
    result = longestRepeatingSubsequence(test2, max_input_len);
    if (result >= 0) {
        printf("Input: \"%s\" -> Longest Repeating Subsequence: %d\n", test2, result);
    }
    
    result = longestRepeatingSubsequence(test3, max_input_len);
    if (result >= 0) {
        printf("Input: \"%s\" -> Longest Repeating Subsequence: %d\n", test3, result);
    }
    
    result = longestRepeatingSubsequence(test4, max_input_len);
    if (result >= 0) {
        printf("Input: \"%s\" -> Longest Repeating Subsequence: %d\n", test4, result);
    }
    
    return 0;
}