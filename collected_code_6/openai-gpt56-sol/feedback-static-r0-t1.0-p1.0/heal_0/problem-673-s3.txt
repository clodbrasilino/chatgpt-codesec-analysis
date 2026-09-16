#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int concatenate_integers(const uint64_t *values, size_t count, uint64_t *result)
{
    uint64_t combined = 0;

    if (values == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t multiplier = 10;

        for (uint64_t value = values[i]; value >= 10; value /= 10) {
            if (multiplier > UINT64_MAX / 10) {
                return -1;
            }
            multiplier *= 10;
        }

        if (combined > (UINT64_MAX - values[i]) / multiplier) {
            return -1;
        }

        combined = combined * multiplier + values[i];
    }

    *result = combined;
    return 0;
}

int main(int argc, char *argv[])
{
    uint64_t *values = NULL;
    uint64_t result = 0;
    int status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s INTEGER [INTEGER ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    values = calloc((size_t)(argc - 1), sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        char *end = NULL;

        if (argv[i][0] == '\0' || argv[i][0] == '-') {
            fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[i]);
            goto cleanup;
        }

        errno = 0;
        values[i - 1] = strtoumax(argv[i], &end, 10);

        if (errno == ERANGE || end == argv[i] || *end != '\0') {
            fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[i]);
            goto cleanup;
        }
    }

    if (concatenate_integers(values, (size_t)(argc - 1), &result) != 0) {
        fputs("Concatenated value exceeds the supported integer range\n", stderr);
        goto cleanup;
    }

    printf("%" PRIu64 "\n", result);
    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}