#include <stdio.h>
#include <limits.h>
#include <stdint.h>

unsigned int set_left_most_unset_bit(unsigned int n) {
    unsigned int result = 0;
    int bit_position = 0;

    while (n & (1U << bit_position)) {
        bit_position++;
    }

    if (bit_position < (sizeof(n) * CHAR_BIT) - 1) {
        result = n | (1U << bit_position);
    } else {
        result = n;
    }

    return result;
}

int main() {
    unsigned int number = 0b101010;
    printf("Original number: %u, Binary: %b\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %b\n", number, number);
    return 0;
}