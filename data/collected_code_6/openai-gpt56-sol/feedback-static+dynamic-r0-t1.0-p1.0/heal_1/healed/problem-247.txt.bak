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
    size_t length;
    size_t left;
    size_t right;
    size_t result_left;
    size_t result_right;

    if (str == NULL) {
        return NULL;
    }

    n = strlen(str);
    if (n == 0) {
        result = malloc(1);
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

    for (size_t i = n; i-- > 0;) {
        dp[i * n + i] = 1;

        for (size_t j = i + 1; j < n; ++j) {
            if (str[i] == str[j]) {
                dp[i * n + j] = (j == i + 1)
                    ? 2
                    : dp[(i + 1) * n + (j - 1)] + 2;
            } else {
                size_t without_right = dp[i * n + (j - 1)];
                size_t without_left = dp[(i + 1) * n + j];

                dp[i * n + j] = without_right > without_left
                    ? without_right
                    : without_left;
            }
        }
    }

    length = dp[n - 1];

    if (length == SIZE_MAX) {
        free(dp);
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    left = 0;
    right = n - 1;
    result_left = 0;
    result_right = length;

    while (left <= right && result_left < result_right) {
        if (left == right) {
            result[result_left] = str[left];
            break;
        }

        if (str[left] == str[right]) {
            size_t inner = right == left + 1
                ? 0
                : dp[(left + 1) * n + (right - 1)];

            if (dp[left * n + right] == inner + 2) {
                result[result_left++] = str[left];
                result[--result_right] = str[right];
                ++left;
                --right;
                continue;
            }
        }

        if (dp[(left + 1) * n + right] >=
            dp[left * n + (right - 1)]) {
            ++left;
        } else {
            --right;
        }
    }

    result[length] = '\0';
    free(dp);
    return result;
}

int main(void)
{
    char input[4096];
    char *subsequence;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t newline = strcspn(input, "\n");

        if (input[newline] == '\n') {
            input[newline] = '\0';
        } else if (!feof(stdin)) {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }
    }

    subsequence = longest_palindromic_subsequence(input);
    if (subsequence == NULL) {
        fprintf(stderr, "Unable to compute the subsequence.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", subsequence) < 0) {
        free(subsequence);
        return EXIT_FAILURE;
    }

    free(subsequence);
    return EXIT_SUCCESS;
}