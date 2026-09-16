#include <stdio.h>
#include <limits.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 13
  *  test case 0 failed: expected 14, got 11
  *  test case 2 failed: expected 15, got 31
  */

unsigned int set_left_most_unset_bit(unsigned int n) {
    unsigned int result = 0;
    int bit_position = 0;

    while (bit_position < (sizeof(n) * CHAR_BIT) && (n & (1U << bit_position))) {
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
    printf("Original number: %u, Binary: %u\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %u\n", number, number);

    number = 13;
    printf("Original number: %u, Binary: %u\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %u\n", number, number);

    number = 0b1111;
    printf("Original number: %u, Binary: %u\n", number, number);
    number = set_left_most_unset_bit(number);
    printf("Number after setting left most unset bit: %u, Binary: %u\n", number, number);

    return 0;
}