#include <stdio.h>
#include <stdint.h>

uint32_t highest_power_of_2(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    
    return n - (n >> 1);
}

int main(void) {
    uint32_t num = 137;
    uint32_t result;

    result = highest_power_of_2(num);
    printf("%u\n", result);

    num = 1024;
    result = highest_power_of_2(num);
    printf("%u\n", result);

    num = 0;
    result = highest_power_of_2(num);
    printf("%u\n", result);

    return 0;
}