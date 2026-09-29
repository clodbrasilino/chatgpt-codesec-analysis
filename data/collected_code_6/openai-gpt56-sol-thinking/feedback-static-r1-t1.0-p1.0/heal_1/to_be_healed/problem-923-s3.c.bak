#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum ScsStatus {
    SCS_SUCCESS = 0,
    SCS_INVALID_ARGUMENT,
    SCS_LENGTH_OVERFLOW,
    SCS_ALLOCATION_FAILURE
};

static enum ScsStatus shortest_common_supersequence_length(
    const char *str1,
    const char *str2,
    size_t *result)
{
    const char *first;
    const char *second;
    size_t first_length;
    size_t second_length;
    size_t *lcs;
    size_t i;
    size_t j;
    size_t total_length;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return SCS_INVALID_ARGUMENT;
    }

    first = str1;
    second = str2;
    first_length = strlen(str1);
    second_length = strlen(str2);

    if (first_length > SIZE_MAX - second_length) {
        return SCS_LENGTH_OVERFLOW;
    }

    total_length = first_length + second_length;

    if (second_length > first_length) {
        const char *temporary_string = first;
        size_t temporary_length = first_length;

        first = second;
        first_length = second_length;
        second = temporary_string;
        second_length = temporary_length;
    }

    if (second_length > (SIZE_MAX / sizeof(*lcs)) - 1U) {
        return SCS_LENGTH_OVERFLOW;
    }

    lcs = calloc(second_length + 1U, sizeof(*lcs));
    if (lcs == NULL) {
        return SCS_ALLOCATION_FAILURE;
    }

    for (i = 1U; i <= first_length; ++i) {
        size_t diagonal = 0U;

        for (j = 1U; j <= second_length; ++j) {
            size_t previous = lcs[j];

            if (first[i - 1U] == second[j - 1U]) {
                lcs[j] = diagonal + 1U;
            } else if (lcs[j - 1U] > lcs[j]) {
                lcs[j] = lcs[j - 1U];
            }

            diagonal = previous;
        }
    }

    *result = total_length - lcs[second_length];
    free(lcs);

    return SCS_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t length;
    enum ScsStatus status;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = shortest_common_supersequence_length(argv[1], argv[2], &length);

    if (status == SCS_ALLOCATION_FAILURE) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (status == SCS_LENGTH_OVERFLOW) {
        fprintf(stderr, "String length is too large.\n");
        return EXIT_FAILURE;
    }

    if (status != SCS_SUCCESS) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);
    return EXIT_SUCCESS;
}