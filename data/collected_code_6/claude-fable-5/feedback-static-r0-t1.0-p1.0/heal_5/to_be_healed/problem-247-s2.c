#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static char *read_line(FILE *stream, size_t *out_len)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    char *tmp;
    int c;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[length++] = (char)c;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';

    tmp = realloc(buffer, length + 1);
    if (tmp != NULL) {
        buffer = tmp;
    }

    if (out_len != NULL) {
        *out_len = length;
    }
    return buffer;
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
    if (lps_len == 0 || lps_len > n) {
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
            result[left] = s[i];
            break;
        }
        if (s[i] == s[j]) {
            result[left] = s[i];
            result[right] = s[j];
            left++;
            right--;
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
    char *input;
    char *lps;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    input = read_line(stdin, &len);
    if (input == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    lps = longest_palindromic_subsequence(input, len + 1);
    if (lps == NULL) {
        fprintf(stderr, "Failed to compute longest palindromic subsequence\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Longest palindromic subsequence: %s\n", lps);
    printf("Length: %zu\n", strnlen(lps, len + 1));

    free(lps);
    free(input);
    return EXIT_SUCCESS;
}