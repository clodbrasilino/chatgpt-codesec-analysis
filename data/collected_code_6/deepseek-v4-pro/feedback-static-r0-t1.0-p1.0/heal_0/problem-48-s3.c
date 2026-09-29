#include <stdio.h>

unsigned int setOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 0xFFFF, 0x55555555, 0xAAAAAAAA};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        unsigned int result = setOddBits(test_values[i]);
        printf("setOddBits(0x%X) = 0x%X\n", test_values[i], result);
    }

    return 0;
}