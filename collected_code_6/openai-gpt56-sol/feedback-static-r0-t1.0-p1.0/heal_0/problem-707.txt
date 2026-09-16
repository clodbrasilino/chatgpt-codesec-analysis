#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_set_bits_upto(uint64_t n, uint64_t *result)
{
    const uint64_t max_safe_n = UINT64_C(8589934591);
    uint64_t total = 0;

    if (result == NULL || n > max_safe_n) {
        return 0;
    }

    while (n != 0) {
        uint64_t highest_power = UINT64_C(1);
        unsigned int exponent = 0;

        while (highest_power <= n / UINT64_C(2)) {
            highest_power <<= 1;
            ++exponent;
        }

        if (exponent != 0) {
            total += (uint64_t)exponent * (highest_power >> 1);
        }

        total += n - highest_power + UINT64_C(1);
        n -= highest_power;
    }

    *result = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2 || argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Usage: %s <non-negative integer up to 8589934591>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(argv[1], &end, 10);
    if (*end != '\0' || parsed > UINT64_C(8589934591)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!count_set_bits_upto((uint64_t)parsed, &result)) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}