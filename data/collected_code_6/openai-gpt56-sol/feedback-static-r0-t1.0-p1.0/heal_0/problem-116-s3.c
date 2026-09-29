#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tuple_to_integer(const uint64_t *values, size_t count, uint64_t *result)
{
    uint64_t number = 0U;

    if (values == NULL || result == NULL || count == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < count; ++i) {
        uint64_t value = values[i];
        uint64_t multiplier = 10U;

        if (value == 0U) {
            return 0;
        }

        while (multiplier <= value) {
            if (multiplier > UINT64_MAX / 10U) {
                return 0;
            }
            multiplier *= 10U;
        }

        if (number > (UINT64_MAX - value) / multiplier) {
            return 0;
        }

        number = number * multiplier + value;
    }

    *result = number;
    return 1;
}

int main(int argc, char *argv[])
{
    uint64_t *values = NULL;
    uint64_t result = 0U;
    size_t count;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s positive_integer [positive_integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);
    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        char *end = NULL;
        uintmax_t parsed;

        errno = 0;
        parsed = strtoumax(argv[i + 1U], &end, 10);

        if (errno == ERANGE || end == argv[i + 1U] || *end != '\0' ||
            argv[i + 1U][0] == '-' || parsed == 0U || parsed > UINT64_MAX) {
            fprintf(stderr, "Invalid positive integer: %s\n", argv[i + 1U]);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (uint64_t)parsed;
    }

    if (!tuple_to_integer(values, count, &result)) {
        fputs("Conversion failed or overflow occurred.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}