#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        if (i > UINT64_MAX / 2U) {
            return 0;
        }

        uint64_t value = 2U * i;
        uint64_t power = 1U;

        for (int exponent = 0; exponent < 5; ++exponent) {
            if (power > UINT64_MAX / value) {
                return 0;
            }
            power *= value;
        }

        if (sum > UINT64_MAX - power) {
            return 0;
        }
        sum += power;
    }

    *result = sum;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_even((uint64_t)input, &result)) {
        fprintf(stderr, "Arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}