#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 4096

int findLongestRepeatingSubsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t n = strnlen(str, MAX_STR_LEN);

    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= n; i++) {
        dp[i] = (int *)calloc((n + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (size_t k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                int a = dp[i][j - 1];
                int b = dp[i - 1][j];
                dp[i][j] = (a > b) ? a : b;
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

int main(void) {
    const char *str = "aabebcdd";
    int length = findLongestRepeatingSubsequence(str);
    
    if (length >= 0) {
        printf("Length of the longest repeating subsequence is %d\n", length);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}