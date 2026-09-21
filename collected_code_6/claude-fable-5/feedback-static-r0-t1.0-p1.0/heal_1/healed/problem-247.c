#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

static char *longest_palindromic_subsequence(const char *str)
{
    size_t n;
    size_t i;
    size_t j;
    size_t len;
    size_t **dp;
    char *result;
    size_t lo;
    size_t hi;
    size_t left;
    size_t right;

    if (str == NULL) {
        return NULL;
    }

    n = strnlen(str, MAX_INPUT_LEN);
    if (n >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (n == 0U) {
        result = malloc(1U);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        dp[i] = calloc(n, sizeof(**dp));
        if (dp[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }

    for (i = 0U; i < n; i++) {
        dp[i][i] = 1U;
    }

    for (len = 2U; len <= n; len++) {
        for (i = 0U; i + len - 1U < n; i++) {
            j = i + len - 1U;
            if (str[i] == str[j]) {
                dp[i][j] = ((len == 2U) ? 0U : dp[i + 1U][j - 1U]) + 2U;
            } else {
                dp[i][j] = (dp[i + 1U][j] > dp[i][j - 1U]) ? dp[i + 1U][j] : dp[i][j - 1U];
            }
        }
    }

    result = malloc(dp[0][n - 1U] + 1U);
    if (result == NULL) {
        for (i = 0U; i < n; i++) {
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }

    lo = 0U;
    hi = n - 1U;
    left = 0U;
    right = dp[0][n - 1U];
    result[right] = '\0';

    while (lo <= hi) {
        if (lo == hi) {
            result[left] = str[lo];
            break;
        }
        if (str[lo] == str[hi]) {
            result[left] = str[lo];
            left++;
            right--;
            result[right] = str[hi];
            if (hi == 0U) {
                break;
            }
            lo++;
            hi--;
        } else if (dp[lo + 1U][hi] >= dp[lo][hi - 1U]) {
            lo++;
        } else {
            hi--;
        }
    }

    for (i = 0U; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    const char *tests[] = { "bbbab", "character", "agbdba", "", "a" };
    size_t i;
    size_t count;

    count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *lps = longest_palindromic_subsequence(tests[i]);
        if (lps == NULL) {
            (void)fprintf(stderr, "Allocation failure for input \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("Input: \"%s\" -> LPS: \"%s\" (length %zu)\n",
                   tests[i], lps, strnlen(lps, MAX_INPUT_LEN)) < 0) {
            free(lps);
            return EXIT_FAILURE;
        }
        free(lps);
    }

    return EXIT_SUCCESS;
}