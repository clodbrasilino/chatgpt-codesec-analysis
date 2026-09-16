#include <stdio.h>
#include <stdint.h>

uint32_t toggleEvenBits(uint32_t num) {
    return num ^ 0xAAAAAAAA;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    uint32_t result = toggleEvenBits(num);
    printf("Original: %u, Toggled Even Bits: %u\n", num, result);
    return 0;
}