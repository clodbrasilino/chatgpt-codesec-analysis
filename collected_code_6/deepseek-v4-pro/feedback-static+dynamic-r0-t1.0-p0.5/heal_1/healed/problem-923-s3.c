#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shortest_common_supersequence_length(const char *str1, const char *str2) {
    int len1, len2;
    int **dp;
    int result;
    int i, j;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    len1 = (int)strlen(str1);
    len2 = (int)strlen(str2);

    if (len1 < 0 || len2 < 0) {
        return -1;
    }

    dp = (int **)malloc((size_t)(len1 + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((size_t)(len2 + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 0; i <= len1; i++) {
        for (j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]) + 1;
            }
        }
    }

    result = dp[len1][len2];

    for (i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";

    int length = shortest_common_supersequence_length(str1, str2);

    if (length != -1) {
        printf("Length of shortest common supersequence: %d\n", length);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}