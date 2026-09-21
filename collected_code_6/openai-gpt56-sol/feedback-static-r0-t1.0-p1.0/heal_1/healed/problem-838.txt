#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>

static long long minimum_swaps(const char *first, size_t first_length,
                               const char *second, size_t second_length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (first == NULL || second == NULL || first_length != second_length) {
        return -1;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 ||
        mismatches_01 > (size_t)LLONG_MAX) {
        return -1;
    }

    return (long long)mismatches_01;
}

static void trim_line_ending(char *line, ssize_t *length)
{
    while (*length > 0 &&
           (line[*length - 1] == '\n' || line[*length - 1] == '\r')) {
        line[--(*length)] = '\0';
    }
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t first_length;
    ssize_t second_length;
    long long result;
    int status = EXIT_FAILURE;

    first_length = getline(&first, &first_capacity, stdin);
    if (first_length < 0) {
        goto cleanup;
    }

    second_length = getline(&second, &second_capacity, stdin);
    if (second_length < 0) {
        goto cleanup;
    }

    trim_line_ending(first, &first_length);
    trim_line_ending(second, &second_length);

    result = minimum_swaps(first, (size_t)first_length,
                           second, (size_t)second_length);

    if (printf("%lld\n", result) < 0) {
        goto cleanup;
    }

    status = result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}