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
    size_t element_count;
    size_t *lcs;
    size_t i;
    size_t j;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return SCS_INVALID_ARGUMENT;
    }

    first = str1;
    second = str2;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

    if (second_length == SIZE_MAX) {
        return SCS_LENGTH_OVERFLOW;
    }

    element_count = second_length + 1U;

    if (element_count > SIZE_MAX / sizeof(*lcs)) {
        return SCS_LENGTH_OVERFLOW;
    }

    lcs = calloc(element_count, sizeof(*lcs));
    if (lcs == NULL) {
        return SCS_ALLOCATION_FAILURE;
    }

    for (i = 0U; i < first_length; ++i) {
        size_t diagonal = 0U;

        for (j = 0U; j < second_length; ++j) {
            size_t previous = lcs[j + 1U];

            if (first[i] == second[j]) {
                lcs[j + 1U] = diagonal + 1U;
            } else if (lcs[j] > lcs[j + 1U]) {
                lcs[j + 1U] = lcs[j];
            }

            diagonal = previous;
        }
    }

    *result = total_length - lcs[second_length];

    free(lcs);
    return SCS_SUCCESS;
}

int main(int argc, char **argv)
{
    size_t length;
    enum ScsStatus status;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fputs("Usage: program <str1> <str2>\n", stderr);
        return EXIT_FAILURE;
    }

    status = shortest_common_supersequence_length(argv[1], argv[2], &length);

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