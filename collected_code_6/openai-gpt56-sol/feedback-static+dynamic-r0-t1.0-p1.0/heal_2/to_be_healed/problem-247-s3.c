#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *longest_palindromic_subsequence(const char *str, size_t n)
{
    size_t cells;
    size_t *dp;
    char *result;
    size_t i;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    size_t left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    size_t right;

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

    dp = calloc(cells, sizeof(*dp));
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

        left = 0U;
        right = length;

        while (i <= j) {
            if (i == j) {
                result[left] = str[i];
                break;
            }

            if (str[i] == str[j]) {
                size_t inner =
                    j > i + 1U
                        ? dp[(i + 1U) * n + (j - 1U)]
                        : 0U;

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
    char *data = NULL;
    size_t capacity = 0U;
    size_t used = 0U;
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used == SIZE_MAX - 1U) {
            free(data);
            return 0;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(data);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= used + 1U) {
                free(data);
                return 0;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(data);
        return 0;
    }

    if (data == NULL) {
        data = malloc(1U);
        if (data == NULL) {
            return 0;
        }
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    char *palindrome;
    size_t input_length;

    if (!read_line(stdin, &input, &input_length)) {
        return EXIT_FAILURE;
    }

    palindrome =
        longest_palindromic_subsequence(input, input_length);
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