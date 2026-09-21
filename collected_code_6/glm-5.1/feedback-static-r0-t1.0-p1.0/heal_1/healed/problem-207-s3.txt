#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubseq(const char *str) {
    size_t n = strnlen(str, 1024 * 1024);
    if (n <= 0) {
        return 0;
    }
    
    int *dp_block = (int *)malloc((n + 1) * (n + 1) * sizeof(int));
    if (dp_block == NULL) {
        return 0;
    }
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        free(dp_block);
        return 0;
    }
    
    for (size_t i = 0; i <= n; i++) {
        dp[i] = dp_block + i * (n + 1);
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
    
    free(dp_block);
    free(dp);
    
    return result;
}

int main() {
    char str1[] = "aabebcdd";
    int res1 = longestRepeatingSubseq(str1);
    printf("%d\n", res1);
    
    char str2[] = "axxxy";
    int res2 = longestRepeatingSubseq(str2);
    printf("%d\n", res2);
    
    return 0;
}