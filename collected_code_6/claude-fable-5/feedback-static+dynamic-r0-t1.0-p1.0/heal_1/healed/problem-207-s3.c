#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

int longestRepeatingSubsequence(const char *str, size_t max_len)
{
    size_t n;
    size_t i;
    size_t j;
    int **dp;
    int result;

    if (str == NULL) {
        return -1;
    }

    n = strnlen(str, max_len);
    if (n == 0) {
        return 0;
    }

    if (n > (SIZE_MAX / sizeof(int *)) - 1) {
        return -1;
    }

    dp = malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i <= n; i++) {
        dp[i] = calloc(n + 1, sizeof(int));
        if (dp[i] == NULL) {
            while (i > 0) {
                i--;
                free(dp[i]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    result = dp[n][n];

    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    int result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = longestRepeatingSubsequence(buffer, sizeof(buffer));
    if (result < 0) {
        fprintf(stderr, "Failed to compute longest repeating subsequence\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest repeating subsequence: %d\n", result);

    return EXIT_SUCCESS;
}