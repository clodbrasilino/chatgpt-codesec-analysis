#include <stdio.h>
#include <stdint.h>

uint32_t left_rotate(uint32_t num, unsigned int bits) {
    bits %= 32;
    if (bits == 0) return num;
    return (num << bits) | (num >> (32 - bits));
}

int main(void) {
    uint32_t number = 0xDEADBEEF;
    unsigned int rotate_by = 8;
    uint32_t rotated = left_rotate(number, rotate_by);
    printf("Original: 0x%08X\n", number);
    printf("Rotated:  0x%08X\n", rotated);

    uint32_t test1 = left_rotate(0x00000001, 1);
    printf("%u\n", test1);

    uint32_t test2 = left_rotate(0x00000001, 31);
    printf("%u\n", test2);

    uint32_t test3 = left_rotate(0x00000001, 32);
    printf("%u\n", test3);

    return 0;
}