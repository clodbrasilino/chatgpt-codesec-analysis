#include <stdio.h>
#include <stdint.h>

unsigned int smallest_power_of_two(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 8, 9, 16, 17, 255, 256, 257, 1024, 1025};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        unsigned int result = smallest_power_of_two(test_values[i]);
        printf("smallest_power_of_two(%u) = %u\n", test_values[i], result);
    }
    
    return 0;
}