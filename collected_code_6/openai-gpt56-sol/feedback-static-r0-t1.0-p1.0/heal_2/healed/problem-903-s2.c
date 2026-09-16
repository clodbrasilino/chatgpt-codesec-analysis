#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int bit_length(uint64_t value)
{
    unsigned int length = 0U;

    do {
        ++length;
        value >>= 1U;
    } while (value != UINT64_C(0));

    return length;
}

static uint64_t count_set_bits_up_to(uint64_t n, unsigned int width)
{
    uint64_t total = UINT64_C(0);

    for (unsigned int bit = 0U; bit < width; ++bit) {
        const uint64_t half = UINT64_C(1) << bit;
        const uint64_t higher =
            bit + 1U < 64U ? n >> (bit + 1U) : UINT64_C(0);
        const uint64_t lower = n & (half - UINT64_C(1));
        const uint64_t current = (n >> bit) & UINT64_C(1);

        total += higher * half;

        if (current != UINT64_C(0)) {
            total += lower + UINT64_C(1);
        }
    }

    return total;
}

static uint64_t count_unset_bits(uint64_t n)
{
    const unsigned int width = bit_length(n);
    const uint64_t range_size = n + UINT64_C(1);
    const uint64_t total_positions = range_size * (uint64_t)width;
    const uint64_t set_bits = count_set_bits_up_to(n, width);
    const uint64_t power_of_two = UINT64_C(1) << width;
    const uint64_t leading_positions =
        power_of_two - range_size - UINT64_C(1);

    return total_positions - set_bits - leading_positions - (uint64_t)width;
}

int main(int argc, const char *const argv[])
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
        input == UINTMAX_C(0) || input > UINT32_MAX) {
        fprintf(stderr, "n must be an integer from 1 to %" PRIu32 "\n",
                UINT32_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_unset_bits((uint64_t)input));

    return EXIT_SUCCESS;
}