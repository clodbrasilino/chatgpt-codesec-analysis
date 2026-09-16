#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static size_t right_insertion_point(const int *values, size_t length, int target)
{
    size_t low = 0;
    size_t high = length;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (values[middle] <= target) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int *values = NULL;
    int target;
    size_t length;
    size_t position;
    int exit_status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s target [sorted_values...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int(argv[1], &target)) {
        fprintf(stderr, "Invalid target: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    length = (size_t)(argc - 2);

    if (length > 0) {
        if (length > SIZE_MAX / sizeof(*values)) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!parse_int(argv[i + 2], &values[i])) {
            fprintf(stderr, "Invalid value: %s\n", argv[i + 2]);
            goto cleanup;
        }

        if (i > 0 && values[i - 1] > values[i]) {
            fprintf(stderr, "Values must be sorted in nondecreasing order\n");
            goto cleanup;
        }
    }

    position = right_insertion_point(values, length, target);

    if (printf("%zu\n", position) < 0) {
        perror("printf");
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(values);
    return exit_status;
}