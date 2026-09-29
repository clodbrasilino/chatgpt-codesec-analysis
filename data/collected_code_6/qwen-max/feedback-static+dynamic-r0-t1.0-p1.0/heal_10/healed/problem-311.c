#include <stdio.h>
#include <limits.h>
#include <stdint.h>

unsigned int set_left_most_unset_bit(unsigned int n) {
    unsigned int mask = 1U << (sizeof(n) * CHAR_BIT - 1);
    while (mask && (n & mask)) {
        mask >>= 1;
    }
    return n | mask;
}

int main() {
    unsigned int number = 0b101010;
    printf("Original number: %u, Binary: %b\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %b\n", number, number);

    number = 13;
    printf("Original number: %u, Binary: %b\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %b\n", number, number);

    number = 0b1111;
    printf("Original number: %u, Binary: %b\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %b\n", number, number);

    return 0;
}