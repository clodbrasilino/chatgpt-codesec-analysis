#include <stdio.h>
#include <stdint.h>

uint64_t smallest_power_of_2(uint64_t n) {
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
    uint64_t inputs[] = {0, 1, 2, 3, 4, 5, 15, 16, 17, 0xFFFFFFFFFFFFFFFF};
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    
    for (size_t i = 0; i < count; i++) {
        uint64_t result = smallest_power_of_2(inputs[i]);
        printf("smallest_power_of_2(%llu) = %llu\n", (unsigned long long)inputs[i], (unsigned long long)result);
    }
    
    return 0;
}