#include <stdio.h>

unsigned int toggle_bits(unsigned int num) {
    // Getting the number of bits in unsigned int
    int num_bits = sizeof(unsigned int) * 8;
    // Mask to toggle first and last bits
    unsigned int mask = (1 << (num_bits - 1)) | 1;
    // Toggling first and last bits
    return num ^ mask;
}

int main() {
    unsigned int num = 10;
    unsigned int result = toggle_bits(num);
    printf("Result: %u\n", result);
    return 0;
}