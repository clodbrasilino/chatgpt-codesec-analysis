#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SCS_ARGUMENT_SCAN_LIMIT ((size_t)1048577U)

enum ScsStatus {
    SCS_SUCCESS = 0,
    SCS_INVALID_ARGUMENT,
    SCS_LENGTH_OVERFLOW,
    SCS_ALLOCATION_FAILURE
};

static enum ScsStatus bounded_string_length(
    const char *string,
    size_t scan_limit,
    size_t *result)
{
    size_t length;

    if (string == NULL || result == NULL || scan_limit == 0U) {
        return SCS_INVALID_ARGUMENT;
    }

    for (length = 0U; length < scan_limit; ++length) {
        if (string[length] == '\0') {
            *result = length;
            return SCS_SUCCESS;
        }
    }

    return SCS_LENGTH_OVERFLOW;
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
    size_t element_count;
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

static int report_status(enum ScsStatus status)
{
    switch (status) {
        case SCS_ALLOCATION_FAILURE:
            fputs("Memory allocation failed.\n", stderr);
            break;

        case SCS_LENGTH_OVERFLOW:
            fputs("String length is too large or not terminated.\n", stderr);
            break;

        case SCS_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument.\n", stderr);
            break;
    }

    return EXIT_FAILURE;
}

int main(int argc, char **argv)
{
    size_t str1_length;
    size_t str2_length;
    size_t result;
    enum ScsStatus status;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fputs("Usage: program <str1> <str2>\n", stderr);
        return EXIT_FAILURE;
    }

    status = bounded_string_length(
        argv[1],
        SCS_ARGUMENT_SCAN_LIMIT,
        &str1_length);

    if (status != SCS_SUCCESS) {
        return report_status(status);
    }

    status = bounded_string_length(
        argv[2],
        SCS_ARGUMENT_SCAN_LIMIT,
        &str2_length);

    if (status != SCS_SUCCESS) {
        return report_status(status);
    }

    status = shortest_common_supersequence_length(
        argv[1],
        str1_length,
        argv[2],
        str2_length,
        &result);

    if (status != SCS_SUCCESS) {
        return report_status(status);
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}