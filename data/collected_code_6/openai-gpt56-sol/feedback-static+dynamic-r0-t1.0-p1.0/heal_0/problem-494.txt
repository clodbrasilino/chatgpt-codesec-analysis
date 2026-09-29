#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_tuple_to_uint64(const unsigned int tuple[], size_t length,
                                  uint64_t *result)
{
    uint64_t value = 0;

    if (tuple == NULL || result == NULL || length == 0U || length > 64U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (tuple[i] > 1U) {
            return -1;
        }

        value = (value << 1U) | (uint64_t)tuple[i];
    }

    *result = value;
    return 0;
}

int main(void)
{
    unsigned int tuple[64];
    size_t length;
    uint64_t result;

    if (scanf("%zu", &length) != 1 || length == 0U || length > 64U) {
        fputs("Invalid tuple length\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%u", &tuple[i]) != 1) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (binary_tuple_to_uint64(tuple, length, &result) != 0) {
        fputs("Tuple must contain only 0 and 1\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}