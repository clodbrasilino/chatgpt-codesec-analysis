#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 10000

int findLongestRepeatingSubseq(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int n = 0;
    while (str[n] != '\0' && n < MAX_STR_LEN) {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = (dp[i][j - 1] > dp[i - 1][j]) ? dp[i][j - 1] : dp[i - 1][j];
            }
        }
    }

    int res = dp[n][n];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return res;
}

int main(void) {
    char str[] = "AABEBCDD";
    int length = findLongestRepeatingSubseq(str);
    printf("%d\n", length);
    return 0;
}