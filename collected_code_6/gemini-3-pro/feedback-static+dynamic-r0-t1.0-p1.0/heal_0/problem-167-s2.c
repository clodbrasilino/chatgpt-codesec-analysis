#include <stdio.h>
#include <stdint.h>

uint64_t next_power_of_2(uint64_t n) {
    if (n == 0) {
        return 1;
    }
    
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    n++;
    
    return n;
}

int main(void) {
    uint64_t test_values[] = {0, 1, 2, 3, 4, 15, 16, 17, 100, 1024, 1025};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        uint64_t n = test_values[i];
        uint64_t result = next_power_of_2(n);
        printf("Next power of 2 for %llu is %llu\n", (unsigned long long)n, (unsigned long long)result);
    }
    
    return 0;
}