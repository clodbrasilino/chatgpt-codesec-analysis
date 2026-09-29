#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALLOWED_LEN 100000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestRepeatingSubsequence(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Either the condition 'len<100000' is redundant or the array 'str[9]' is accessed at index 99999, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     *  Assuming that condition 'len<100000' is not redundant
     */
    while (len < MAX_ALLOWED_LEN && str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return 0;
    }

    int n = (int)len;

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
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