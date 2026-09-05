#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

char* longest_common_subsequence(const char* X, const char* Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    if (dp == NULL) {
        return NULL;
    }
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    int lcs_len = dp[m][n];
    char* lcs = (char*)malloc((lcs_len + 1) * sizeof(char));
    if (lcs == NULL) {
        for (int i = 0; i <= m; i++) {
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }
    
    int i = m, j = n;
    int index = lcs_len;
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
    
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
    
    return lcs;
}

int main() {
    const char* X = "AGGTAB";
    const char* Y = "GXTXAYB";
    
    char* result = longest_common_subsequence(X, Y);
    if (result != NULL) {
        printf("Longest Common Subsequence: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}