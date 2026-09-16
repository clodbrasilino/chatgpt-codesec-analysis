#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int shortest_supersequence_length(const char *str1, const char *str2)
{
    size_t m;
    size_t n;
    size_t i;
    size_t j;
    int result;
    int **dp;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    m = strlen(str1);
    n = strlen(str2);

    dp = malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i <= m; i++) {
        dp[i] = malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = (int)j;
            } else if (j == 0) {
                dp[i][j] = (int)i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] < dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j] + 1;
                } else {
                    dp[i][j] = dp[i][j - 1] + 1;
                }
            }
        }
    }

    result = dp[m][n];

    for (i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    const char *str1 = "geek";
    const char *str2 = "eke";
    int length;

    length = shortest_supersequence_length(str1, str2);
    if (length < 0) {
        fprintf(stderr, "Error computing supersequence length\n");
        return EXIT_FAILURE;
    }

    if (printf("Length of the shortest supersequence is %d\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}