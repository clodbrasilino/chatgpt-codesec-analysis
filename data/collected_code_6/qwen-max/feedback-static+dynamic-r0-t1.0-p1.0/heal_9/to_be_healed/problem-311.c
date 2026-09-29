#include <stdio.h>
#include <limits.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 13
  *  test case 0 failed: expected 14, got 11
  */

unsigned int set_left_most_unset_bit(unsigned int n) {
    unsigned int result = 0;
    int bit_position = 0;
    unsigned int mask = 1U << (sizeof(n) * CHAR_BIT - 1);

    while (mask && (n & mask)) {
        mask >>= 1;
        bit_position++;
    }

    if (bit_position < (sizeof(n) * CHAR_BIT)) {
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