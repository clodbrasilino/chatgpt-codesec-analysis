#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortest_supersequence(const char *str1, size_t m, const char *str2, size_t n) {
    size_t total_elements = (m + 1) * (n + 1);
    int *dp_block = (int *)malloc(total_elements * sizeof(int));
    if (dp_block == NULL) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        free(dp_block);
        return -1;
    }

    for (size_t i = 0; i <= m; i++) {
        dp[i] = dp_block + i * (n + 1);
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
    free(dp);
    free(dp_block);
    return result;
}

int main() {
    const char str1[] = "AGGTAB";
    const char str2[] = "GXTXAYB";
    
    size_t str1_len = strnlen(str1, sizeof(str1));
    size_t str2_len = strnlen(str2, sizeof(str2));
    
    if (str1_len >= 256 || str2_len >= 256) {
        return 1;
    }

    char *str1_buf = (char *)malloc(256 * sizeof(char));
    if (str1_buf == NULL) {
        return 1;
    }

    char *str2_buf = (char *)malloc(256 * sizeof(char));
    if (str2_buf == NULL) {
        free(str1_buf);
        return 1;
    }

    snprintf(str1_buf, 256, "%s", str1);
    snprintf(str2_buf, 256, "%s", str2);
    
    int result = shortest_supersequence(str1_buf, strnlen(str1_buf, 256), str2_buf, strnlen(str2_buf, 256));
    printf("%d\n", result);
    
    free(str1_buf);
    free(str2_buf);
    return 0;
}