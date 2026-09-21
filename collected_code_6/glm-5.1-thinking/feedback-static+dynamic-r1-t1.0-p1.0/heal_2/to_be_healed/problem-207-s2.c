#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int longest_repeating_subsequence(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    size_t n = 0;
    while (n < SIZE_MAX - 1 && str[n] != '\0') {
        n++;
    }
    if (n == SIZE_MAX - 1 && str[n] != '\0') {
        return -1;
    }
    
    if (n == 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'dims=n+1', assigned value is greater than 0
     */
    size_t dims = n + 1;
    /* Possible weaknesses found:
     *  Condition 'dims==0' is always false
     *  Condition 'dims==0' is always false [knownConditionTrueFalse]
     */
    if (dims == 0) {
        return -1;
    }
    if (dims > SIZE_MAX / dims) {
        return -1;
    }
    size_t sq = dims * dims;
    if (sq > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    size_t size = sq * sizeof(int);
    
    int *dp = (int *)malloc(size);
    if (dp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i * dims + j] = 0;
            } else if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * dims + j] = dp[(i - 1) * dims + (j - 1)] + 1;
            } else {
                int val1 = dp[(i - 1) * dims + j];
                int val2 = dp[i * dims + (j - 1)];
                dp[i * dims + j] = (val1 > val2) ? val1 : val2;
            }
        }
    }
    
    int result = dp[n * dims + n];
    free(dp);
    return result;
}

int main(void) {
    const char *str = "aabebcdd";
    int result = longest_repeating_subsequence(str);
    printf("%d\n", result);
    return 0;
}