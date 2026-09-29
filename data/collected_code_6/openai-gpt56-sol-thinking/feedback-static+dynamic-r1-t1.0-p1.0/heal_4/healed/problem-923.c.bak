#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int shortest_string_length(const char *str1, const char *str2,
                                  size_t *result)
{
    size_t len1;
    size_t len2;
    size_t *dp;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return -1;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

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

    for (size_t i = 1; i <= len1; ++i) {
        size_t diagonal = 0;

        for (size_t j = 1; j <= len2; ++j) {
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

int main(int argc, char *const argv[])
{
    size_t length;

    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <str1> <str2>\n", program_name);
        return EXIT_FAILURE;
    }

    if (shortest_string_length(argv[1], argv[2], &length) != 0) {
        fprintf(stderr,
                "Unable to calculate the shortest string length\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}