#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int bit_length(uint64_t value)
{
    unsigned int length = 0U;

    while (value != 0U) {
        ++length;
        value >>= 1U;
    }

    return length;
}

static uint64_t count_set_bits_up_to(uint64_t n)
{
    uint64_t total = 0U;

    for (unsigned int bit = 0U; bit < 64U; ++bit) {
        const uint64_t half = UINT64_C(1) << bit;
        const uint64_t higher =
            bit == 63U ? UINT64_C(0) : (n >> (bit + 1U));
        const uint64_t lower = n & (half - UINT64_C(1));

        total += higher * half;

        if (((n >> bit) & UINT64_C(1)) != 0U) {
            total += lower + UINT64_C(1);
        }
    }

    return total;
}

static uint64_t count_unset_bits(uint64_t n)
{
    const unsigned int width = bit_length(n);
    const uint64_t count = n + UINT64_C(1);
    const uint64_t total_positions = count * (uint64_t)width;
    const uint64_t set_bits = count_set_bits_up_to(n);

    return total_positions - set_bits;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0U || input > UINT32_MAX) {
        fprintf(stderr, "n must be an integer from 1 to %" PRIu32 "\n",
                UINT32_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_unset_bits((uint64_t)input));

    return EXIT_SUCCESS;
}