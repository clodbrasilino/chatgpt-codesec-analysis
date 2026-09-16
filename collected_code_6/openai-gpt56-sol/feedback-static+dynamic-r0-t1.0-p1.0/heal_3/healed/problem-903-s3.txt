#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_total_bits(uint64_t n)
{
    uint64_t total = 0;
    uint64_t start = 1;
    unsigned int width = 1;

    while (start <= n) {
        uint64_t end;
        uint64_t upper;
        uint64_t count;

        if (start > UINT64_MAX / 2) {
            end = UINT64_MAX;
        } else {
            end = start * 2 - 1;
        }

        upper = n < end ? n : end;
        count = upper - start + 1;
        total += count * (uint64_t)width;

        if (end >= n || start > UINT64_MAX / 2) {
            break;
        }

        start *= 2;
        ++width;
    }

    return total;
}

static uint64_t count_set_bits(uint64_t n)
{
    uint64_t total = 0;

    for (unsigned int bit = 0; bit < 64; ++bit) {
        uint64_t half = UINT64_C(1) << bit;
        uint64_t complete_cycles;

        if (bit == 63) {
            complete_cycles = 0;
        } else {
            complete_cycles = (n + 1) >> (bit + 1);
        }

        total += complete_cycles * half;

        if ((n & half) != 0) {
            total += (n & (half - 1)) + 1;
        }
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
    const char *program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", program_name);
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