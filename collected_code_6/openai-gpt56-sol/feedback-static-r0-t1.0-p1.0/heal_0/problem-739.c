#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int smallest_triangular_index(unsigned int digits, uint64_t *index)
{
    uint64_t threshold = 1;
    uint64_t low = 1;
    uint64_t high = 1;

    if (index == NULL || digits == 0 || digits > 19) {
        return -1;
    }

    for (unsigned int i = 1; i < digits; ++i) {
        if (threshold > UINT64_MAX / 10) {
            return -1;
        }
        threshold *= 10;
    }

    while (((__uint128_t)high * (high + 1)) / 2 < threshold) {
        if (high > UINT64_MAX / 2) {
            return -1;
        }
        high *= 2;
    }

    while (low < high) {
        uint64_t mid = low + (high - low) / 2;
        __uint128_t triangular = (__uint128_t)mid * (mid + 1) / 2;

        if (triangular >= threshold) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    *index = low;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long value;
    uint64_t index;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || value == 0 || value > 19) {
        fprintf(stderr, "Invalid digit count\n");
        return EXIT_FAILURE;
    }

    if (smallest_triangular_index((unsigned int)value, &index) != 0) {
        fprintf(stderr, "Unable to compute the index\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", index);
    return EXIT_SUCCESS;
}