#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *longest_palindromic_subsequence(const char *str, size_t n)
{
    if (str == NULL && n != 0) {
        return NULL;
    }

    if (n == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (n > SIZE_MAX / n) {
        return NULL;
    }

    size_t cells = n * n;
    if (cells > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    size_t *dp = calloc(cells, sizeof(*dp));
    if (dp == NULL) {
        return NULL;
    }

    for (size_t i = n; i-- > 0;) {
        dp[i * n + i] = 1;

        for (size_t j = i + 1; j < n; ++j) {
            if (str[i] == str[j]) {
                dp[i * n + j] =
                    (j == i + 1) ? 2 : dp[(i + 1) * n + j - 1] + 2;
            } else {
                size_t skip_left = dp[(i + 1) * n + j];
                size_t skip_right = dp[i * n + j - 1];

                dp[i * n + j] =
                    skip_left > skip_right ? skip_left : skip_right;
            }
        }
    }

    size_t result_length = dp[n - 1];

    if (result_length == SIZE_MAX) {
        free(dp);
        return NULL;
    }

    char *result = malloc(result_length + 1);
    if (result == NULL) {
        free(dp);
        return NULL;
    }

    size_t i = 0;
    size_t j = n - 1;
    size_t left = 0;
    size_t right = result_length;

    while (i < j) {
        size_t inner_length =
            (j == i + 1) ? 0 : dp[(i + 1) * n + j - 1];

        if (str[i] == str[j] &&
            dp[i * n + j] == inner_length + 2) {
            result[left++] = str[i];
            result[--right] = str[j];
            ++i;
            --j;
        } else if (dp[(i + 1) * n + j] >= dp[i * n + j - 1]) {
            ++i;
        } else {
            --j;
        }
    }

    if (i == j && left < right) {
        result[left] = str[i];
    }

    result[result_length] = '\0';
    free(dp);
    return result;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    size_t capacity = 64;
    char *data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    size_t used = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(data);
            return -1;
        }

        if (used + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *temporary = realloc(data, new_capacity);

            if (temporary == NULL) {
                free(data);
                return -1;
            }

            data = temporary;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0;

    if (read_line(stdin, &input, &input_length) != 0) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    char *result =
        longest_palindromic_subsequence(input, input_length);

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