#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SCS_OK = 0,
    SCS_INVALID_ARGUMENT,
    SCS_SIZE_OVERFLOW,
    SCS_ALLOCATION_FAILURE
} ScsStatus;

static ScsStatus shortest_common_supersequence_length(
    const char *str1,
    const char *str2,
    size_t *result)
{
    const char *long_str;
    const char *short_str;
    size_t long_len;
    size_t short_len;
    size_t len1;
    size_t len2;
    size_t row_count;
    size_t *row;
    size_t i;
    size_t j;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return SCS_INVALID_ARGUMENT;
    }

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 > SIZE_MAX - len2) {
        return SCS_SIZE_OVERFLOW;
    }

    if (len1 >= len2) {
        long_str = str1;
        long_len = len1;
        short_str = str2;
        short_len = len2;
    } else {
        long_str = str2;
        long_len = len2;
        short_str = str1;
        short_len = len1;
    }

    if (short_len == SIZE_MAX) {
        return SCS_SIZE_OVERFLOW;
    }

    row_count = short_len + 1;

    if (row_count > SIZE_MAX / sizeof(*row)) {
        return SCS_SIZE_OVERFLOW;
    }

    row = calloc(row_count, sizeof(*row));
    if (row == NULL) {
        return SCS_ALLOCATION_FAILURE;
    }

    for (i = 0; i < long_len; ++i) {
        size_t diagonal = 0;

        for (j = 0; j < short_len; ++j) {
            size_t previous = row[j + 1];

            if (long_str[i] == short_str[j]) {
                row[j + 1] = diagonal + 1;
            } else if (row[j] > row[j + 1]) {
                row[j + 1] = row[j];
            }

            diagonal = previous;
        }
    }

    *result = len1 + len2 - row[short_len];

    free(row);
    return SCS_OK;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    size_t length;
    ScsStatus status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <str1> <str2>\n", program_name);
        return EXIT_FAILURE;
    }

    status = shortest_common_supersequence_length(
        argv[1],
        argv[2],
        &length
    );

    switch (status) {
        case SCS_OK:
            break;

        case SCS_INVALID_ARGUMENT:
            fprintf(stderr, "Invalid argument\n");
            return EXIT_FAILURE;

        case SCS_SIZE_OVERFLOW:
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;

        case SCS_ALLOCATION_FAILURE:
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;

        default:
            fprintf(stderr, "Unexpected error\n");
            return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}