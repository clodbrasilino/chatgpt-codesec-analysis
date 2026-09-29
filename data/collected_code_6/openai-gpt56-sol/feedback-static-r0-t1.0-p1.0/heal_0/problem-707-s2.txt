#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_set_bits(uint64_t n)
{
    uint64_t total = 0;

    while (n != 0) {
        unsigned int bit = 63U - (unsigned int)__builtin_clzll(n);
        uint64_t power = UINT64_C(1) << bit;
        uint64_t bits_up_to_power = bit == 0U
            ? 0U
            : (uint64_t)bit * (power >> 1U);

        total += bits_up_to_power;
        total += n - power + 1U;
        n -= power;
    }

    return total;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_set_bits((uint64_t)value));
    return EXIT_SUCCESS;
}