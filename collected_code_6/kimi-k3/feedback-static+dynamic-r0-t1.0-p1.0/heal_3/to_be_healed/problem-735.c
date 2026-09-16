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
    uint32_t test_cases[] = {0xFU, 0xAU, 0xBU};
    /* Possible weaknesses found:
     *  Variable 'expected' is assigned a value that is never used. [unreadVariable]
     */
    uint32_t expected[] = {15U, 12U, 13U};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        uint32_t result = toggle_middle_bits(test_cases[i]);
        printf("%u\n", result);
    }
    
    return 0;
}