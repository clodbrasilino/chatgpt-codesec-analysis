#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 1024

static size_t bounded_strlen(const char *str, size_t maxlen)
{
    size_t len = 0;

    while (len < maxlen && str[len] != '\0') {
        len++;
    }

    return len;
}

int longestRepeatingSubsequence(const char *str, size_t maxlen)
{
    size_t n;
    size_t i;
    size_t j;
    size_t limit;
    int **dp;
    int result;

    if (str == NULL || maxlen == 0) {
        return -1;
    }

    n = bounded_strlen(str, maxlen);
    if (n == maxlen && str[maxlen - 1] != '\0') {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    limit = (sizeof(int *) > sizeof(int)) ? (SIZE_MAX / sizeof(int *)) : (SIZE_MAX / sizeof(int));
    if (n >= limit - 1) {
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

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;
    const size_t guard_limit = 1048576;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_limit);
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

    len = bounded_strlen(buffer, MAX_INPUT_LEN);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == (size_t)(MAX_INPUT_LEN - 1)) {
        discard_remaining_input();
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