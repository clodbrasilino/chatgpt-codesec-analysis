#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int bit_length(uint64_t value)
{
    unsigned int length = 0;

    do {
        ++length;
        value >>= 1U;
    } while (value != 0U);

    return length;
}

static uint64_t count_set_bits_up_to(uint64_t n)
{
    uint64_t total = 0U;

    /* Possible weaknesses found:
     *  Assuming that condition 'bit<64U' is not redundant
     */
    for (unsigned int bit = 0U; bit < 64U; ++bit) {
        const uint64_t half = UINT64_C(1) << bit;
        /* Possible weaknesses found:
         *  Shift
         *  Shifting 64-bit value by 64 bits is undefined behaviour [shiftTooManyBits]
         */
        const uint64_t higher = n >> (bit + 1U);
        const uint64_t lower = n & (half - 1U);
        const uint64_t current = (n >> bit) & UINT64_C(1);

        total += higher * half;

        if (current != 0U) {
            total += lower + UINT64_C(1);
        }
    }

    return total;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 7
  *  test case 2 failed: expected 17, got 28
  *  test case 0 failed: expected 1, got 2
  */

static uint64_t count_unset_bits(uint64_t n)
{
    const unsigned int width = bit_length(n);
    const uint64_t range_size = n + UINT64_C(1);
    const uint64_t total_positions = range_size * (uint64_t)width;
    const uint64_t set_bits = count_set_bits_up_to(n);
    const uint64_t leading_positions =
        ((UINT64_C(1) << width) - range_size) - UINT64_C(1);

    return total_positions - set_bits - leading_positions - (uint64_t)width;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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