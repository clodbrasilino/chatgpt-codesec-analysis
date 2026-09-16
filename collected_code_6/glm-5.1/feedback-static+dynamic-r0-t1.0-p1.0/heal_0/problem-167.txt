#include <stdio.h>
#include <stdint.h>

uint32_t next_power_of_2(uint32_t n) {
    if (n == 0) {
        return 1;
    }
    if ((n & (n - 1)) == 0) {
        return n;
    }
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 5, 16, 17, 1000000000};
    size_t count = sizeof(test_values) / sizeof(test_values[0]);
    for (size_t i = 0; i < count; i++) {
        printf("%u -> %u\n", test_values[i], next_power_of_2(test_values[i]));
    }
    return 0;
}