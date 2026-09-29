#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 1024U

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static int longest_repeating_subsequence(const char *str, size_t n)
{
    size_t i;
    size_t j;
    int result;
    int **dp;

    if (str == NULL || n == 0U) {
        return 0;
    }

    if (n >= SIZE_MAX) {
        return -1;
    }

    if ((n + 1U) > (SIZE_MAX / sizeof(int *))) {
        return -1;
    }

    if ((n + 1U) > (SIZE_MAX / sizeof(int))) {
        return -1;
    }

    dp = (int **)malloc((n + 1U) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i <= n; i++) {
        dp[i] = (int *)calloc(n + 1U, sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 1U; i <= n; i++) {
        for (j = 1U; j <= n; j++) {
            if ((str[i - 1U] == str[j - 1U]) && (i != j)) {
                dp[i][j] = dp[i - 1U][j - 1U] + 1;
            } else {
                dp[i][j] = max_int(dp[i - 1U][j], dp[i][j - 1U]);
            }
        }
    }

    result = dp[n][n];

    for (i = 0U; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;

    do {
        ch = getchar();
        guard++;
    } while ((ch != '\n') && (ch != EOF) && (guard < (size_t)INT32_MAX));
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0U || size > (size_t)INT32_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    } else if (len == (size - 1U)) {
        discard_remaining_input();
    }

    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;
    int result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));

    result = longest_repeating_subsequence(buffer, len);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of the longest repeating subsequence: %d\n", result);

    return EXIT_SUCCESS;
}