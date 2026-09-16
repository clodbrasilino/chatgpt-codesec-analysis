#include <stdio.h>
#include <stdint.h>

uint32_t left_rotate(uint32_t num, unsigned int n) {
    n %= 32;
    if (n == 0) {
        return num;
    }
    return (num << n) | (num >> (32 - n));
}

int main(void) {
    uint32_t num = 0x12345678;
    unsigned int rotate_by = 4;
    uint32_t result = left_rotate(num, rotate_by);
    printf("Original: 0x%08X\n", num);
    printf("Rotated left by %u: 0x%08X\n", rotate_by, result);
    return 0;
}