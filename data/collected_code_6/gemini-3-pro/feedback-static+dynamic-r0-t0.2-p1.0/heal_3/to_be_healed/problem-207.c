#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int n = 0;
    
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'n<4096' is not redundant
     *  Either the condition 'n<4096' is redundant or the array 'str[9]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (n < MAX_STR_LEN && str[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    int result = dp[n][n];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    const char *str = "AABEBCDD";
    int length = longestRepeatingSubsequence(str);
    
    if (length != -1) {
        printf("%d\n", length);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}