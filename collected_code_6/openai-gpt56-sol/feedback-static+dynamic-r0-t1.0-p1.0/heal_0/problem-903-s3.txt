#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_total_bits(uint64_t n)
{
    uint64_t total = 0U;
    uint64_t start = 1U;
    unsigned int width = 1U;

    while (start <= n) {
        const uint64_t end = start > UINT64_MAX / 2U
                                 ? UINT64_MAX
                                 : (start * 2U) - 1U;
        const uint64_t upper = n < end ? n : end;
        const uint64_t count = upper - start + 1U;

        total += count * (uint64_t)width;

        if (upper == n) {
            break;
        }

        start *= 2U;
        ++width;
    }

    return total;
}

static uint64_t count_set_bits(uint64_t n)
{
    uint64_t total = 0U;

    while (n != 0U) {
        unsigned int bit = 0U;

        while (bit < 64U) {
            const uint64_t half = UINT64_C(1) << bit;
            const uint64_t remainder = n - half + 1U;

            total += (n >> (bit + 1U)) * half;
            if ((n & half) != 0U) {
                total += remainder < half ? remainder : half;
            }

            if (bit == 63U) {
                break;
            }
            ++bit;
        }
        break;
    }

    return total;
}

static int count_unset_bits(uint64_t n, uint64_t *result)
{
    uint64_t total_bits;
    uint64_t set_bits;

    if (result == NULL) {
        return -1;
    }

    total_bits = count_total_bits(n);
    set_bits = count_set_bits(n);

    if (set_bits > total_bits) {
        return -1;
    }

    *result = total_bits - set_bits;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fputs("Invalid input: n must be an integer from 0 to 4294967295.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (count_unset_bits((uint64_t)input, &result) != 0) {
        fputs("Unable to calculate the result.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}