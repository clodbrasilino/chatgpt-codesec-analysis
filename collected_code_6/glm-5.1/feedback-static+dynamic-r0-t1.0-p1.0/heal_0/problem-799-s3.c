#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t left_rotate_bits(uint32_t num, uint32_t d) {
    uint32_t shift = d % 32;
    if (shift == 0) {
        return num;
    }
    return (num << shift) | (num >> (32 - shift));
}

int main(void) {
    uint32_t num = 0x12345678;
    uint32_t d = 4;
    uint32_t result = left_rotate_bits(num, d);
    printf("%" PRIu32 "\n", result);
    return 0;
}