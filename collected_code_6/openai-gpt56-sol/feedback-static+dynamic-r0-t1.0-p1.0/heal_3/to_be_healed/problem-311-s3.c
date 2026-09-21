#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t mask = UINT32_C(1);

    while ((value & mask) != 0U && mask != 0U) {
        mask <<= 1U;
    }

    return mask == 0U ? value : value | mask;
}

int main(void)
{
    uint32_t value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[64];
    char extra;

    if (fgets(line, sizeof line, stdin) == NULL ||
        sscanf(line, " %" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));
    return 0;
}