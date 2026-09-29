#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int total_unset_bits(uint64_t n, uint64_t *result)
{
    uint64_t total_bits = 0;
    uint64_t set_bits = 0;
    uint64_t range_start = 1;

    if (result == NULL) {
        return -1;
    }

    for (unsigned int bit = 0; bit < 64U && (n >> bit) != 0U; ++bit) {
        const uint64_t half = UINT64_C(1) << bit;
        const uint64_t full_cycles = (n >> bit) >> 1;
        const uint64_t remainder = n & ((half << 1) - 1U);
        const uint64_t extra = remainder >= half ? remainder - half + 1U : 0U;

        if (full_cycles > (UINT64_MAX - set_bits - extra) / half) {
            return -1;
        }

        set_bits += full_cycles * half + extra;

        if (range_start <= (UINT64_MAX >> 1)) {
            const uint64_t count = n - range_start + 1U;

            if (count > (UINT64_MAX - total_bits) / (bit + 1U)) {
                return -1;
            }

            total_bits += count * (bit + 1U);
            range_start <<= 1;
        }
    }

    if (set_bits > total_bits) {
        return -1;
    }

    *result = total_bits - set_bits;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == NULL || *end != '\0' ||
        parsed == 0U || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (total_unset_bits((uint64_t)parsed, &result) != 0) {
        fputs("Result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}