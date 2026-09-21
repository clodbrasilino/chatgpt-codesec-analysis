#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum ScsStatus {
    SCS_SUCCESS = 0,
    SCS_INVALID_ARGUMENT,
    SCS_LENGTH_OVERFLOW,
    SCS_ALLOCATION_FAILURE
};

static size_t command_argument_length(const char *argument)
{
    size_t length = 0U;

    while (argument[length] != '\0') {
        ++length;
    }

    return length;
}

static enum ScsStatus shortest_common_supersequence_length(
    const char *str1,
    size_t str1_length,
    const char *str2,
    size_t str2_length,
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

    if (str1_length > SIZE_MAX - str2_length) {
        return SCS_LENGTH_OVERFLOW;
    }

    total_length = str1_length + str2_length;
    first = str1;
    second = str2;
    first_length = str1_length;
    second_length = str2_length;

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

int main(int argc, char *argv[const])
{
    const char *str1;
    const char *str2;
    size_t str1_length;
    size_t str2_length;
    size_t length;
    enum ScsStatus status;

    if (argc != 3) {
        fputs("Usage: program <str1> <str2>\n", stderr);
        return EXIT_FAILURE;
    }

    str1 = argv[1];
    str2 = argv[2];
    str1_length = command_argument_length(str1);
    str2_length = command_argument_length(str2);

    status = shortest_common_supersequence_length(
        str1,
        str1_length,
        str2,
        str2_length,
        &length
    );

    switch (status) {
        case SCS_SUCCESS:
            printf("%zu\n", length);
            return EXIT_SUCCESS;

        case SCS_ALLOCATION_FAILURE:
            fputs("Memory allocation failed.\n", stderr);
            break;

        case SCS_LENGTH_OVERFLOW:
            fputs("String length is too large.\n", stderr);
            break;

        case SCS_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument.\n", stderr);
            break;
    }

    return EXIT_FAILURE;
}