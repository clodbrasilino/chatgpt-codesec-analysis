#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static char *longest_palindromic_subsequence(const char *str, size_t n)
{
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
                dp[i * n + j] = j == i + 1
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
    char *input;
    char *subsequence;
    size_t input_length;

    input = read_line(stdin);
    if (input == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    subsequence = longest_palindromic_subsequence(input, input_length);
    free(input);

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