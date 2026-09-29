#include <stdio.h>

unsigned int toggle_odd_bits(unsigned int num) {
    unsigned int mask = 0xAA;
    return num ^ mask;
}

int main() {
    unsigned int number = 0x55;
    printf("Original number: %u\n", number);
    unsigned int result = toggle_odd_bits(number);
    printf("Number with odd bits toggled: %u\n", result);
    return 0;
}