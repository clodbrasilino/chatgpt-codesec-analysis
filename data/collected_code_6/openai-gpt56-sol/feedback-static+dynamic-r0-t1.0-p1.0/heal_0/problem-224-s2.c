#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(uint64_t value)
{
    unsigned int count = 0U;

    while (value != UINT64_C(0)) {
        value &= value - UINT64_C(1);
        ++count;
    }

    return count;
}

int main(void)
{
    uint64_t value = UINT64_C(0);

    if (scanf("%" SCNu64, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_set_bits(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}