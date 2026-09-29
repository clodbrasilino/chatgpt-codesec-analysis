#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int shortest_common_supersequence_length(
    const char *str1,
    size_t len1,
    const char *str2,
    size_t len2,
    size_t *result)
{
    if (str1 == NULL || str2 == NULL || result == NULL) {
        return -1;
    }

    if (len1 > SIZE_MAX - len2 || len2 == SIZE_MAX) {
        return -1;
    }

    const size_t column_count = len2 + 1;

    if (column_count > SIZE_MAX / sizeof(size_t)) {
        return -1;
    }

    size_t *dp = calloc(column_count, sizeof(*dp));

    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 1; i <= len1; ++i) {
        size_t previous_diagonal = 0;

        for (size_t j = 1; j <= len2; ++j) {
            const size_t previous_row = dp[j];

            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = previous_diagonal + 1;
            } else if (dp[j - 1] > dp[j]) {
                dp[j] = dp[j - 1];
            }

            previous_diagonal = previous_row;
        }
    }

    *result = len1 + len2 - dp[len2];
    free(dp);
    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 3) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <str1> <str2>\n", program);
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    const size_t len1 = strlen(argv[1]);
    const size_t len2 = strlen(argv[2]);
    size_t length = 0;

    if (shortest_common_supersequence_length(
            argv[1], len1, argv[2], len2, &length) != 0) {
        fputs("Failed to compute the shortest length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}