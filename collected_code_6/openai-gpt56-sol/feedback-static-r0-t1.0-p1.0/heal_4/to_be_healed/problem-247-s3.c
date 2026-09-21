#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static char *longest_palindromic_subsequence(const char *str, size_t n)
{
    size_t cells;
    size_t *dp;
    char *result;
    size_t i;
    size_t length;

    if (str == NULL) {
        return NULL;
    }

    if (n == 0U) {
        result = malloc(1U);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (n > SIZE_MAX / n) {
        return NULL;
    }

    cells = n * n;

    if (cells > SIZE_MAX / sizeof(*dp)) {
        return NULL;
    }

    dp = malloc(cells * sizeof(*dp));
    if (dp == NULL) {
        return NULL;
    }

    for (i = n; i-- > 0U;) {
        size_t j;

        dp[i * n + i] = 1U;

        for (j = i + 1U; j < n; ++j) {
            if (str[i] == str[j]) {
                dp[i * n + j] = 2U;

                if (j > i + 1U) {
                    dp[i * n + j] += dp[(i + 1U) * n + (j - 1U)];
                }
            } else {
                size_t without_right = dp[i * n + (j - 1U)];
                size_t without_left = dp[(i + 1U) * n + j];

                dp[i * n + j] =
                    without_left > without_right
                        ? without_left
                        : without_right;
            }
        }
    }

    length = dp[n - 1U];

    if (length == SIZE_MAX) {
        free(dp);
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    i = 0U;

    {
        size_t j = n - 1U;
        size_t left = 0U;
        size_t right = length;

        while (i <= j) {
            if (i == j) {
                if (left < right) {
                    result[left] = str[i];
                }
                break;
            }

            if (str[i] == str[j]) {
                size_t inner = 0U;

                if (j > i + 1U) {
                    inner = dp[(i + 1U) * n + (j - 1U)];
                }

                if (dp[i * n + j] == inner + 2U) {
                    result[left++] = str[i];
                    result[--right] = str[j];
                    ++i;
                    --j;
                    continue;
                }
            }

            if (dp[(i + 1U) * n + j] >=
                dp[i * n + (j - 1U)]) {
                ++i;
            } else {
                --j;
            }
        }
    }

    result[length] = '\0';
    free(dp);
    return result;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = 64U;
    size_t used = 0U;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2U;
            new_data = realloc(data, new_capacity);

            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (used > 0U && data[used - 1U] == '\r') {
        --used;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *palindrome = NULL;
    size_t input_length = 0U;

    if (!read_line(stdin, &input, &input_length)) {
        return EXIT_FAILURE;
    }

    palindrome = longest_palindromic_subsequence(input, input_length);
    free(input);

    if (palindrome == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(palindrome, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        free(palindrome);
        return EXIT_FAILURE;
    }

    free(palindrome);
    return EXIT_SUCCESS;
}