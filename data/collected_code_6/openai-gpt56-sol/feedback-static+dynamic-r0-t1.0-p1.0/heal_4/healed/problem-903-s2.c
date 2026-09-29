#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_set_bits_up_to(uint64_t n)
{
    uint64_t total = 0;

    for (unsigned int bit = 0; bit < 32; ++bit) {
        const uint64_t half = UINT64_C(1) << bit;
        const uint64_t period = half << 1;
        const uint64_t count = n + 1;
        const uint64_t complete_periods = count / period;
        const uint64_t remainder = count % period;

        total += complete_periods * half;

        if (remainder > half) {
            total += remainder - half;
        }
    }

    return total;
}

static uint64_t count_unset_bits(uint64_t n)
{
    uint64_t total_positions = 0;

    for (unsigned int bit = 0; bit < 32; ++bit) {
        const uint64_t first_value = UINT64_C(1) << bit;

        if (first_value > n) {
            break;
        }

        total_positions += n - first_value + 1;
    }

    return total_positions - count_set_bits_up_to(n);
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
        input == 0 || input > UINT32_MAX) {
        fprintf(stderr, "n must be an integer from 1 to %" PRIu32 "\n",
                UINT32_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_unset_bits((uint64_t)input));

    return EXIT_SUCCESS;
}