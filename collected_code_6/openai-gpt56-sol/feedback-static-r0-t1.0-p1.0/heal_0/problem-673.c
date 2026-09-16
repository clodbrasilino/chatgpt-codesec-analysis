#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int concatenate_integers(const uint32_t *values, size_t count, uint64_t *result)
{
    uint64_t combined = 0;

    if (values == NULL || result == NULL || count == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t multiplier = 10;
        uint32_t value = values[i];

        for (uint32_t remaining = value; remaining >= 10; remaining /= 10) {
            if (multiplier > UINT64_MAX / 10) {
                return -1;
            }
            multiplier *= 10;
        }

        if (combined > (UINT64_MAX - value) / multiplier) {
            return -1;
        }

        combined = combined * multiplier + value;
    }

    *result = combined;
    return 0;
}

int main(int argc, char *argv[])
{
    uint32_t *values = NULL;
    uint64_t result = 0;
    int status = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((size_t)(argc - 1) > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Too many integers\n");
        return EXIT_FAILURE;
    }

    values = malloc((size_t)(argc - 1) * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        char *end = NULL;
        uintmax_t parsed;

        if (argv[i][0] == '\0' || argv[i][0] == '-') {
            fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[i]);
            goto cleanup;
        }

        errno = 0;
        parsed = strtoumax(argv[i], &end, 10);

        if (errno == ERANGE || end == argv[i] || *end != '\0' ||
            parsed > UINT32_MAX) {
            fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[i]);
            goto cleanup;
        }

        values[i - 1] = (uint32_t)parsed;
    }

    if (concatenate_integers(values, (size_t)(argc - 1), &result) != 0) {
        fprintf(stderr, "Combined integer exceeds uint64_t range\n");
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    return status;
}