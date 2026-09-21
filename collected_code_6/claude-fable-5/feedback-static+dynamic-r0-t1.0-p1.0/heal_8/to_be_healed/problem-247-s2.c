#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT 1024

static void free_table(size_t **table, size_t rows)
{
    size_t i;

    if (table == NULL) {
        return;
    }
    for (i = 0; i < rows; i++) {
        free(table[i]);
    }
    free(table);
}

static char *longest_palindromic_subsequence(const char *s, size_t max_len)
{
    size_t n;
    size_t i;
    size_t j;
    size_t len;
    size_t left;
    size_t right;
    size_t lps_len;
    size_t **dp;
    char *result;

    if (s == NULL) {
        return NULL;
    }

    n = strnlen(s, max_len);
    if (n == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (n > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    dp = calloc(n, sizeof *dp);
    if (dp == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        dp[i] = calloc(n, sizeof **dp);
        if (dp[i] == NULL) {
            free_table(dp, i);
            return NULL;
        }
    }

    for (i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (len = 2; len <= n; len++) {
        for (i = 0; i + len - 1 < n; i++) {
            j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = (dp[i + 1][j] > dp[i][j - 1]) ? dp[i + 1][j] : dp[i][j - 1];
            }
        }
    }

    lps_len = dp[0][n - 1];
    if (lps_len == 0 || lps_len > SIZE_MAX - 1 || lps_len > n) {
        free_table(dp, n);
        return NULL;
    }

    result = malloc(lps_len + 1);
    if (result == NULL) {
        free_table(dp, n);
        return NULL;
    }

    i = 0;
    j = n - 1;
    left = 0;
    right = lps_len - 1;
    while (i <= j) {
        if (i == j) {
            if (left < lps_len) {
                result[left] = s[i];
            }
            break;
        }
        if (s[i] == s[j]) {
            if (left < lps_len && right < lps_len) {
                result[left] = s[i];
                result[right] = s[j];
            }
            left++;
            if (right > 0) {
                right--;
            } else {
                right = lps_len;
            }
            i++;
            j--;
        } else if (dp[i + 1][j] >= dp[i][j - 1]) {
            i++;
        } else {
            j--;
        }
    }
    result[lps_len] = '\0';

    free_table(dp, n);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    char *lps;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    input[sizeof input - 1] = '\0';

    len = strnlen(input, sizeof input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    lps = longest_palindromic_subsequence(input, sizeof input);
    if (lps == NULL) {
        fprintf(stderr, "Failed to compute longest palindromic subsequence\n");
        return EXIT_FAILURE;
    }

    printf("Longest palindromic subsequence: %s\n", lps);
    printf("Length: %zu\n", strnlen(lps, MAX_INPUT));

    free(lps);
    return EXIT_SUCCESS;
}