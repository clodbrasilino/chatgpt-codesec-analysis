#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1024

static size_t safe_strnlen(const char *str, size_t max_len)
{
    size_t i;

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }
    return i;
}

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

    n = safe_strnlen(str, max_len);
    if (n == 0) {
        return 0;
    }

    if (n >= (SIZE_MAX / sizeof(int *)) - 1) {
        return -1;
    }
    if (n >= (SIZE_MAX / sizeof(int)) - 1) {
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
    char *buffer;
    int result;
    size_t len;

    buffer = calloc(MAX_INPUT_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_LEN - 1] = '\0';

    len = safe_strnlen(buffer, MAX_INPUT_LEN);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = longestRepeatingSubsequence(buffer, MAX_INPUT_LEN);
    if (result < 0) {
        fprintf(stderr, "Failed to compute longest repeating subsequence\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Length of longest repeating subsequence: %d\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}