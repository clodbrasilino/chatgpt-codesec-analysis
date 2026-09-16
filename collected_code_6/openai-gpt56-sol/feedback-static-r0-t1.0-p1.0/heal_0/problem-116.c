#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tuple_to_integer(const uint32_t *tuple, size_t length, uint64_t *result)
{
    uint64_t value = 0;

    if (tuple == NULL || result == NULL || length == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        uint64_t multiplier = 10U;
        uint32_t element = tuple[i];

        if (element == 0U) {
            return -1;
        }

        for (uint32_t n = element; n >= 10U; n /= 10U) {
            if (multiplier > UINT64_MAX / 10U) {
                return -1;
            }
            multiplier *= 10U;
        }

        if (value > (UINT64_MAX - element) / multiplier) {
            return -1;
        }

        value = value * multiplier + element;
    }

    *result = value;
    return 0;
}

int main(int argc, char *argv[])
{
    uint32_t *tuple = NULL;
    uint64_t result = 0;
    size_t length;
    int status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s positive_integer...\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = (size_t)(argc - 1);

    if (length > SIZE_MAX / sizeof(*tuple)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    tuple = malloc(length * sizeof(*tuple));
    if (tuple == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        char *end = NULL;
        uintmax_t value;

        errno = 0;
        value = strtoumax(argv[i + 1U], &end, 10);

        if (errno == ERANGE || end == argv[i + 1U] || *end != '\0' ||
            argv[i + 1U][0] == '-' || value == 0U || value > UINT32_MAX) {
            fprintf(stderr, "Invalid positive integer: %s\n", argv[i + 1U]);
            goto cleanup;
        }

        tuple[i] = (uint32_t)value;
    }

    if (tuple_to_integer(tuple, length, &result) != 0) {
        fputs("The converted integer exceeds the supported range.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuple);
    return status;
}