#include <stdio.h>
#include <stdint.h>

#define BIT_SIZE 32

uint32_t left_rotate_bits(uint32_t num, unsigned int rotation) {
    if (rotation >= BIT_SIZE) {
        rotation %= BIT_SIZE;
    }
    return (num << rotation) | (num >> (BIT_SIZE - rotation));
}

int main() {
    uint32_t num = 123456;
    unsigned int rotation = 3;

    uint32_t result = left_rotate_bits(num, rotation);
    printf("Result: %u\n", result);

    return 0;
}