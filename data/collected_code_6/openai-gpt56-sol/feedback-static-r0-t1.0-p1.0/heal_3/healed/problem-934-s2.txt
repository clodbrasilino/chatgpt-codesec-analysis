#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_delannoy(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;
    uint64_t previous = 0;

    if (result == NULL) {
        return 0;
    }

    for (unsigned int k = 0; k < n; ++k) {
        const uint64_t factor = 6U * (uint64_t)k + 3U;
        const uint64_t adjustment = (uint64_t)k;

        if (value > UINT64_MAX / factor) {
            return 0;
        }

        const uint64_t product = factor * value;

        if (adjustment != 0U &&
            previous > (UINT64_MAX - product) / adjustment) {
            return 0;
        }

        const uint64_t numerator = product + adjustment * previous;

        previous = value;
        value = numerator / ((uint64_t)k + 1U);
    }

    *result = value;
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 ||
        end == argv[1] ||
        *end != '\0' ||
        input > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!nth_delannoy((unsigned int)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}