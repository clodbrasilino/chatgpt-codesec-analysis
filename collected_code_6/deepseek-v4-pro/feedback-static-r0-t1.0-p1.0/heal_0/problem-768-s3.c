#include <stdio.h>
#include <stdint.h>

int is_odd_parity(uint32_t num) {
    uint32_t parity = 0;
    while (num) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return parity & 1;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 7, 8, 15, 16, 255, 256};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("%u: %s\n", test_values[i], 
               is_odd_parity(test_values[i]) ? "odd parity" : "even parity");
    }
    
    return 0;
}