#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int findShortestSupersequenceLength(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, MAX_STR_LEN);
    size_t len2 = strnlen(str2, MAX_STR_LEN);

    if (len1 == MAX_STR_LEN || len2 == MAX_STR_LEN) {
        return -1;
    }

    int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= len1; i++) {
        dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
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
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
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
    
    int length = findShortestSupersequenceLength(str1, str2);
    if (length != -1) {
        printf("%d\n", length);
    } else {
        fprintf(stderr, "Error calculating length.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}