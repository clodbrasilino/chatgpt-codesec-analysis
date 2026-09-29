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
    size_t total_length;
    size_t *lcs;
    size_t i;
    size_t j;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return SCS_INVALID_ARGUMENT;
    }

    first = str1;
    second = str2;
    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length > SIZE_MAX - second_length) {
        return SCS_LENGTH_OVERFLOW;
    }

    total_length = first_length + second_length;

    if (second_length > first_length) {
        const char *temporary_string = first;
        const size_t temporary_length = first_length;

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
            const size_t previous = lcs[j];

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

int main(int argc, char * const argv[])
{
    const char *program_name;
    size_t length;
    enum ScsStatus status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", program_name);
        return EXIT_FAILURE;
    }

    status = shortest_common_supersequence_length(argv[1], argv[2], &length);

    switch (status) {
        case SCS_SUCCESS:
            printf("%zu\n", length);
            return EXIT_SUCCESS;

        case SCS_ALLOCATION_FAILURE:
            fprintf(stderr, "Memory allocation failed.\n");
            break;

        case SCS_LENGTH_OVERFLOW:
            fprintf(stderr, "String length is too large.\n");
            break;

        case SCS_INVALID_ARGUMENT:
        default:
            fprintf(stderr, "Invalid argument.\n");
            break;
    }

    return EXIT_FAILURE;
}