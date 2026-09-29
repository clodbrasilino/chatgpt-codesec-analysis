#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    return value | (value + UINT32_C(1));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    uint32_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    if (sscanf(input, " %" SCNu32 " %c", &value, &extra) != 1) {
        return 1;
    }

    printf("%" PRIu32 "\n", set_rightmost_unset_bit(value));
    return 0;
}