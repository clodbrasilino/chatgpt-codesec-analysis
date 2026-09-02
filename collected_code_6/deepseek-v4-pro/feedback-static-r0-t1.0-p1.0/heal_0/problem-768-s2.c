#include <stdio.h>
#include <stdint.h>

int has_odd_parity(uint32_t num) {
    num ^= num >> 16;
    num ^= num >> 8;
    num ^= num >> 4;
    num &= 0xf;
    return (0x6996 >> num) & 1;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 7, 8, 15, 16, 255, 256, 65535, 65536, 0xFFFFFFFF};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("Number: %u, Odd parity: %d\n", test_values[i], has_odd_parity(test_values[i]));
    }
    
    return 0;
}