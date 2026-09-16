#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_numbers_with_bits_set(uint64_t limit, unsigned int n)
{
    uint64_t block_size;
    uint64_t half_block;
    uint64_t full_blocks;
    uint64_t remainder;
    uint64_t count;

    if (n >= 64U || limit == 0U) {
        return 0U;
    }

    if (n == 63U) {
        return limit > (UINT64_C(1) << 63U)
                   ? limit - (UINT64_C(1) << 63U)
                   : 0U;
    }

    half_block = UINT64_C(1) << n;
    block_size = half_block << 1U;
    full_blocks = limit / block_size;
    remainder = limit % block_size;
    count = full_blocks * half_block;

    if (remainder > half_block) {
        count += remainder - half_block;
    }

    return count;
}

int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t parsed_limit;
    uintmax_t parsed_n;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <exclusive_limit> <bit_n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_limit = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_limit > UINT64_MAX || argv[1][0] == '-') {
        (void)fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_n = strtoumax(argv[2], &end, 10);

    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        parsed_n >= 64U || argv[2][0] == '-') {
        (void)fprintf(stderr, "Invalid bit position\n");
        return EXIT_FAILURE;
    }

    (void)printf(
        "%" PRIu64 "\n",
        count_numbers_with_bits_set(
            (uint64_t)parsed_limit,
            (unsigned int)parsed_n
        )
    );

    return EXIT_SUCCESS;
}