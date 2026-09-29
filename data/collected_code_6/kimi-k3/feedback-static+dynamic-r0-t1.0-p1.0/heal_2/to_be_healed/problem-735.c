#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 15, got <no output>
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 13, got <no output>
  */

uint32_t toggle_middle_bits(uint32_t value) {
    if (value <= 1U) {
        return value;
    }
    uint32_t msb_pos = 31U - __builtin_clz(value);
    uint32_t msb_mask = 1U << msb_pos;
    uint32_t lsb_mask = 1U;
    uint32_t middle_mask = ((msb_mask - 1U) & ~lsb_mask);
    return value ^ middle_mask;
}

int main(void) {
    uint32_t number = 0xB5U;
    uint32_t result = toggle_middle_bits(number);
    printf("Original: 0x%X\n", number);
    printf("Result:   0x%X\n", result);
    return 0;
}