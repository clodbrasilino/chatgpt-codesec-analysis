#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000000

size_t safe_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int shortestCommonSupersequenceLength(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    int m = (int)safe_strlen(str1);
    int n = (int)safe_strlen(str2);

    if (m >= MAX_LEN || n >= MAX_LEN) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";

    int length = shortestCommonSupersequenceLength(str1, str2);
    if (length != -1) {
        printf("%d\n", length);
    }

    return 0;
}