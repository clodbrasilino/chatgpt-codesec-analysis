#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U

static int longest_repeating_subsequence(const char *str, size_t len)
{
    size_t i;
    size_t j;
    int result;
    int **dp;

    if (str == NULL || len == 0U) {
        return 0;
    }

    if (len > MAX_INPUT_LENGTH) {
        return -1;
    }

    dp = (int **)malloc((len + 1U) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i <= len; i++) {
        dp[i] = (int *)calloc(len + 1U, sizeof(int));
        if (dp[i] == NULL) {
            size_t k;
            for (k = 0U; k < i; k++) {
                free(dp[k]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 1U; i <= len; i++) {
        for (j = 1U; j <= len; j++) {
            if ((str[i - 1U] == str[j - 1U]) && (i != j)) {
                dp[i][j] = dp[i - 1U][j - 1U] + 1;
            } else {
                if (dp[i - 1U][j] > dp[i][j - 1U]) {
                    dp[i][j] = dp[i - 1U][j];
                } else {
                    dp[i][j] = dp[i][j - 1U];
                }
            }
        }
    }

    result = dp[len][len];

    for (i = 0U; i <= len; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0U;
    }

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }

    return max_len;
}

int main(void)
{
    const char *test_strings[] = { "aabb", "axxzxy", "abc", "aab" };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0U; i < num_tests; i++) {
        size_t len = bounded_strlen(test_strings[i], MAX_INPUT_LENGTH);
        int result = longest_repeating_subsequence(test_strings[i], len);
        if (result < 0) {
            (void)fprintf(stderr, "Memory allocation failed for input: %s\n",
                          test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Longest repeating subsequence length of \"%s\" is %d\n",
                   test_strings[i], result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}