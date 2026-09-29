#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)4096)

static int bounded_string_length(const char *const string,
                                 size_t *const result)
{
    size_t length;

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (length = 0; length <= MAX_INPUT_LENGTH; ++length) {
        if (string[length] == '\0') {
            *result = length;
            return 0;
        }
    }

    return -1;
}

static int shortest_string_length(const char *const string1,
                                  const char *const string2,
                                  size_t *const result)
{
    const char *longer_string;
    const char *shorter_string;
    size_t length1;
    size_t length2;
    size_t longer_length;
    size_t shorter_length;
    size_t element_count;
    size_t *dp;
    size_t i;
    size_t j;

    if (string1 == NULL || string2 == NULL || result == NULL) {
        return -1;
    }

    if (bounded_string_length(string1, &length1) != 0 ||
        bounded_string_length(string2, &length2) != 0) {
        return -1;
    }

    if (length1 > SIZE_MAX - length2) {
        return -1;
    }

    if (length1 >= length2) {
        longer_string = string1;
        shorter_string = string2;
        longer_length = length1;
        shorter_length = length2;
    } else {
        longer_string = string2;
        shorter_string = string1;
        longer_length = length2;
        shorter_length = length1;
    }

    if (shorter_length == SIZE_MAX) {
        return -1;
    }

    element_count = shorter_length + 1;

    if (element_count > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = calloc(element_count, sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (i = 1; i <= longer_length; ++i) {
        size_t diagonal = 0;

        for (j = 1; j <= shorter_length; ++j) {
            const size_t previous = dp[j];

            if (longer_string[i - 1] == shorter_string[j - 1]) {
                dp[j] = diagonal + 1;
            } else if (dp[j - 1] > dp[j]) {
                dp[j] = dp[j - 1];
            }

            diagonal = previous;
        }
    }

    *result = length1 + length2 - dp[shorter_length];

    free(dp);
    return 0;
}

int main(int argc, char **const argv)
{
    const char *program_name = "program";
    size_t length;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", program_name);
        return EXIT_FAILURE;
    }

    if (shortest_string_length(argv[1], argv[2], &length) != 0) {
        fputs("Unable to calculate the shortest string length\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}