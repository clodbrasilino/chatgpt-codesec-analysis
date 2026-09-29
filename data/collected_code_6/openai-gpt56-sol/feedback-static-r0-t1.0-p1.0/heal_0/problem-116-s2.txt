#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tuple_to_integer(const uint32_t *tuple, size_t length, uint64_t *result)
{
    uint64_t value = 0;

    if (tuple == NULL || result == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        uint32_t number = tuple[i];

        if (number == 0U) {
            return -1;
        }

        uint64_t multiplier = 10U;
        while (number >= multiplier) {
            if (multiplier > UINT64_MAX / 10U) {
                return -1;
            }
            multiplier *= 10U;
        }

        if (value > (UINT64_MAX - number) / multiplier) {
            return -1;
        }

        value = value * multiplier + number;
    }

    *result = value;
    return 0;
}

int main(int argc, char *argv[])
{
    uint32_t *tuple = NULL;
    uint64_t result = 0;
    int status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s positive_integer [...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    tuple = calloc((size_t)(argc - 1), sizeof(*tuple));
    if (tuple == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        char *end = NULL;

        errno = 0;
        uintmax_t value = strtoumax(argv[i], &end, 10);

        if (errno != 0 || end == argv[i] || *end != '\0' ||
            argv[i][0] == '-' || value == 0 || value > UINT32_MAX) {
            fprintf(stderr, "Invalid positive integer: %s\n", argv[i]);
            goto cleanup;
        }

        tuple[i - 1] = (uint32_t)value;
    }

    if (tuple_to_integer(tuple, (size_t)(argc - 1), &result) != 0) {
        fprintf(stderr, "Conversion failed\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuple);
    return status;
}