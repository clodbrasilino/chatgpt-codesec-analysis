#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH ((size_t)4096)

static int bounded_string_length(const char *str, size_t *result)
{
    size_t length;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (length = 0; length <= MAX_INPUT_LENGTH; ++length) {
        if (str[length] == '\0') {
            *result = length;
            return 0;
        }
    }

    return -1;
}

static int shortest_string_length(const char *str1, const char *str2,
                                  size_t *result)
{
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    size_t *dp;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return -1;
    }

    if (bounded_string_length(str1, &len1) != 0 ||
        bounded_string_length(str2, &len2) != 0) {
        return -1;
    }

    if (len1 > SIZE_MAX - len2) {
        return -1;
    }

    if (len2 > len1) {
        const char *temp_str = str1;
        size_t temp_len = len1;

        str1 = str2;
        str2 = temp_str;
        len1 = len2;
        len2 = temp_len;
    }

    if (len2 == SIZE_MAX ||
        len2 + 1 > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = calloc(len2 + 1, sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (i = 1; i <= len1; ++i) {
        size_t diagonal = 0;

        for (j = 1; j <= len2; ++j) {
            size_t previous = dp[j];

            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = diagonal + 1;
            } else if (dp[j - 1] > dp[j]) {
                dp[j] = dp[j - 1];
            }

            diagonal = previous;
        }
    }

    *result = len1 + len2 - dp[len2];
    free(dp);

    return 0;
}

int main(int argc, char *argv[const])
{
    size_t length;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (shortest_string_length(argv[1], argv[2], &length) != 0) {
        fputs("Unable to calculate the shortest string length\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}