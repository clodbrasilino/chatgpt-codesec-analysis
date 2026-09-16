#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 13
  *  test case 2 failed: expected 15, got 31
  *  test case 0 failed: expected 14, got 11
  */

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    uint32_t bit = UINT32_C(1);

    while (bit != 0 && (value & bit) != 0) {
        bit <<= 1;
    }

    return bit == 0 ? value : value | bit;
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", set_rightmost_unset_bit(value));
    return 0;
}