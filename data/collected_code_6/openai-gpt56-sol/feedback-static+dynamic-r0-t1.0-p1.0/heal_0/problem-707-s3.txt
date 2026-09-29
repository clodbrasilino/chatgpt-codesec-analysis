#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int count_total_set_bits(uint64_t n, uint64_t *result)
{
    uint64_t total = 0;

    if (result == NULL) {
        return -1;
    }

    while (n != 0U) {
        uint64_t power = 1U;
        unsigned int exponent = 0U;

        while (power <= n / 2U) {
            power <<= 1U;
            ++exponent;
        }

        if (exponent != 0U) {
            total += (uint64_t)exponent * (power >> 1U);
        }

        total += n - power + 1U;
        n -= power;
    }

    *result = total;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count_total_set_bits((uint64_t)parsed, &result) != 0) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}