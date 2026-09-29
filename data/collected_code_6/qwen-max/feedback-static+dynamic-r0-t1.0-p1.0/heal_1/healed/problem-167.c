#include <stdio.h>
#include <stdint.h>

uint32_t next_power_of_2(uint32_t n) {
    if (n == 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

int main() {
    uint32_t test_cases[] = {0, 1, 8, 32};
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); ++i) {
        uint32_t n = test_cases[i];
        uint32_t result = next_power_of_2(n);
        printf("The smallest power of 2 greater than or equal to %u is %u\n", n, result);
    }
    return 0;
}