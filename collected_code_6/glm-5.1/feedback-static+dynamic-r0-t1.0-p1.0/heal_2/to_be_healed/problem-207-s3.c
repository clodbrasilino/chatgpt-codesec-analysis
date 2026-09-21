#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

size_t longestRepeatingSubseq(const char *str, size_t str_len) {
    size_t n = str_len;
    /* Possible weaknesses found:
     *  Checking if unsigned expression 'n' is less than zero. [unsignedLessThanZero]
     */
    if (n <= 0) {
        return 0;
    }
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    
    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    int result = dp[n][n];
    
    for (size_t i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    char str1[] = "aabebcdd";
    size_t len1 = sizeof(str1) - 1;
    size_t res1 = longestRepeatingSubseq(str1, len1);
    printf("%zu\n", res1);
    
    char str2[] = "axxxy";
    size_t len2 = sizeof(str2) - 1;
    size_t res2 = longestRepeatingSubseq(str2, len2);
    printf("%zu\n", res2);
    
    return 0;
}