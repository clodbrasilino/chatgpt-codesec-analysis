#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shortest_supersequence_length(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t k = 0; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = (int)j;
            } else if (j == 0) {
                dp[i][j] = (int)i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    int result = dp[len1][len2];

    for (size_t i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    printf("%d\n", shortest_supersequence_length(str1, str2));

    const char *str3 = "ABC";
    const char *str4 = "AC";
    printf("%d\n", shortest_supersequence_length(str3, str4));

    return 0;
}