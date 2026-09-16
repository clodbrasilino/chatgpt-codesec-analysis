#include <stdio.h>
#include <stdint.h>
#include <limits.h>

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
    uint32_t expected[] = {15U, 12U, 13U};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        uint32_t result = toggle_middle_bits(test_cases[i]);
        printf("%u\n", result);
        if (result != expected[i]) {
            printf("Test case %d failed: expected %u, got %u\n", i, expected[i], result);
        }
    }
    
    return 0;
}