#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint32_t next_power_of_2(uint32_t n) {
    if (n == 0) {
        return 1;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 4, 5, 16, 17, 100, 1000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        printf("next_power_of_2(%u) = %u\n", test_values[i], next_power_of_2(test_values[i]));
    }
    
    return 0;
}