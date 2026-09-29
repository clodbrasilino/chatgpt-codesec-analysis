#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t max_size_t(size_t a, size_t b) {
    return (a > b) ? a : b;
}

char* longest_common_subsequence(const char* X, const char* Y, size_t x_len, size_t y_len) {
    size_t m = x_len;
    size_t n = y_len;
    
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    if (dp == NULL) {
        return NULL;
    }
    for (size_t i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }
    
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max_size_t(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    size_t lcs_len = dp[m][n];
    char* lcs = (char*)malloc((lcs_len + 1) * sizeof(char));
    if (lcs == NULL) {
        for (size_t i = 0; i <= m; i++) {
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    
    size_t i = m, j = n;
    size_t index = lcs_len;
    lcs[index] = '\0';
    
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--index] = X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    for (size_t k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
    
    return lcs;
}

int main() {
    const char* X = "AGGTAB";
    const char* Y = "GXTXAYB";
    
    size_t x_len = strnlen(X, 256);
    size_t y_len = strnlen(Y, 256);
    
    char* result = longest_common_subsequence(X, Y, x_len, y_len);
    if (result != NULL) {
        printf("Longest Common Subsequence: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}