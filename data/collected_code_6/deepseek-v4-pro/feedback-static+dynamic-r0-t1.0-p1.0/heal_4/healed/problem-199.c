#include <stdio.h>

unsigned int highest_power_of_two(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned int p = 1;
    while (p <= n) {
        p <<= 1;
    }
    
    return p >> 1;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 8, 9, 15, 16, 17, 31, 32, 33, 64, 100, 255, 256, 1000, 1024, 1025};
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < count; i++) {
        unsigned int input = test_values[i];
        unsigned int result = highest_power_of_two(input);
        printf("highest_power_of_two(%u) = %u\n", input, result);
    }
    
    return 0;
}