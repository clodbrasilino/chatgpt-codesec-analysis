#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)4096)

static int bounded_string_length(const char *str, size_t *result)
{
    size_t length;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (length = 0; length < MAX_INPUT_LENGTH; ++length) {
        if (str[length] == '\0') {
            *result = length;
            return 0;
        }
    }

    if (str[MAX_INPUT_LENGTH] != '\0') {
        return -1;
    }

    *result = MAX_INPUT_LENGTH;
    return 0;
}

static int shortest_string_length(const char *str1, const char *str2,
                                  size_t *result)
{
    size_t len1;
    size_t len2;
    size_t element_count;
    size_t *dp;
    size_t i;
    size_t j;

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
        const char *temporary_string = str1;
        size_t temporary_length = len1;

        str1 = str2;
        str2 = temporary_string;
        len1 = len2;
        len2 = temporary_length;
    }

    if (len2 == SIZE_MAX) {
        return -1;
    }

    element_count = len2 + 1;

    if (element_count > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = calloc(element_count, sizeof(*dp));
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    const char *program_name = "program";
    size_t length;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL ||
        argv[1] == NULL || argv[2] == NULL) {
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