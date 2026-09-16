#include <stdio.h>

unsigned int toggleOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0x12345678};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("Original: 0x%08X, Toggled: 0x%08X\n", test_values[i], toggleOddBits(test_values[i]));
    }
    
    return 0;
}