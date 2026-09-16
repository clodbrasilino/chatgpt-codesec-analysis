#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *longest_palindromic_subsequence(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t n = strlen(str);
    if (n == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    if (n > SIZE_MAX / n || n * n > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    size_t *dp = calloc(n * n, sizeof(*dp));
    if (dp == NULL) {
        return NULL;
    }

    for (size_t i = n; i-- > 0;) {
        dp[i * n + i] = 1;

        for (size_t j = i + 1; j < n; ++j) {
            if (str[i] == str[j]) {
                dp[i * n + j] = (j == i + 1) ? 2 : dp[(i + 1) * n + (j - 1)] + 2;
            } else {
                size_t skip_left = dp[(i + 1) * n + j];
                size_t skip_right = dp[i * n + (j - 1)];
                dp[i * n + j] = skip_left > skip_right ? skip_left : skip_right;
            }
        }
    }

    size_t length = dp[n - 1];
    if (length == SIZE_MAX) {
        free(dp);
        return NULL;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    size_t i = 0;
    size_t j = n - 1;
    size_t left = 0;
    size_t right = length - 1;

    while (i < j) {
        if (str[i] == str[j] &&
            dp[i * n + j] == ((j == i + 1) ? 2 : dp[(i + 1) * n + (j - 1)] + 2)) {
            result[left++] = str[i];
            result[right--] = str[j];
            ++i;
            --j;
        } else if (dp[(i + 1) * n + j] >= dp[i * n + (j - 1)]) {
            ++i;
        } else {
            --j;
        }
    }

    if (i == j) {
        result[left] = str[i];
    }

    result[length] = '\0';
    free(dp);
    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Input error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    char *result = longest_palindromic_subsequence(input);
    free(input);

    if (result == NULL) {
        fputs("Unable to compute the result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}