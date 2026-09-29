#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int find_msb(uint32_t value) {
    if (value == 0U) {
        return -1;
    }
    
    int position = 0;
    
    while (value > 1U) {
        value >>= 1U;
        position++;
    }
    
    return position;
}

int main(void) {
    uint32_t test_values[] = {0U, 1U, 2U, 5U, 8U, 15U, 16U, 255U, 256U, 4294967295U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0U; i < num_tests; i++) {
        int msb = find_msb(test_values[i]);
        if (msb >= 0) {
            printf("Value: %u, MSB position: %d\n", test_values[i], msb);
        } else {
            printf("Value: %u, No set bits\n", test_values[i]);
        }
    }
    
    return 0;
}