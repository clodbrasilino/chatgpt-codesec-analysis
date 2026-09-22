#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortest_supersequence(const char *str1, const char *str2) {
    size_t m = strnlen(str1, SIZE_MAX);
    size_t n = strnlen(str2, SIZE_MAX);
    
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }
    
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] > dp[i][j - 1] ? dp[i][j - 1] : dp[i - 1][j]);
            }
        }
    }
    
    int result = dp[m][n];
    
    for (size_t i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main() {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    
    int length = shortest_supersequence(str1, str2);
    
    if (length != -1) {
        printf("%d\n", length);
    }
    
    return 0;
}