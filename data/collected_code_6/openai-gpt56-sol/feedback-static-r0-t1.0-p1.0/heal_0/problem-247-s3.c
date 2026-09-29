#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *longest_palindromic_subsequence(const char *str)
{
    size_t n;
    size_t cells;
    size_t *dp;
    char *result;
    size_t i;
    size_t length;
    size_t left;
    size_t right;

    if (str == NULL) {
        return NULL;
    }

    n = strlen(str);
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
                    without_left > without_right ? without_left : without_right;
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
    size_t j = n - 1U;
    left = 0U;
    right = length;

    while (i <= j) {
        if (i == j) {
            result[left] = str[i];
            break;
        }

        if (str[i] == str[j]) {
            size_t inner = j > i + 1U ? dp[(i + 1U) * n + (j - 1U)] : 0U;

            if (dp[i * n + j] == inner + 2U) {
                result[left++] = str[i];
                result[--right] = str[j];
                ++i;
                --j;
                continue;
            }
        }

        if (dp[(i + 1U) * n + j] >= dp[i * n + (j - 1U)]) {
            ++i;
        } else {
            --j;
        }
    }

    result[length] = '\0';
    free(dp);
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *palindrome;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    palindrome = longest_palindromic_subsequence(input);
    free(input);

    if (palindrome == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", palindrome) < 0) {
        free(palindrome);
        return EXIT_FAILURE;
    }

    free(palindrome);
    return EXIT_SUCCESS;
}