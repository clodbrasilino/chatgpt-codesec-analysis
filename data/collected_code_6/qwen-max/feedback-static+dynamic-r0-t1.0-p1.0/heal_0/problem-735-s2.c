#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_bit_set(unsigned int num, unsigned int position) {
    return (num & (1 << position)) != 0;
}

unsigned int toggle_bits_except_first_last(unsigned int num) {
    unsigned int result = num;
    int bit_position = 1;
    while ((INT_MAX >> bit_position) > 0) {
        if (bit_position > 0 && bit_position < (sizeof(unsigned int) * 8 - 1)) {
            if (is_bit_set(num, bit_position)) {
                result &= ~(1 << bit_position);
            } else {
                result |= (1 << bit_position);
            }
        }
        bit_position++;
    }
    return result;
}

int main() {
    unsigned int num = 0b10101010;
    unsigned int toggled_num = toggle_bits_except_first_last(num);
    printf("Original: %u (binary: %08b)\n", num, num);
    printf("Toggled: %u (binary: %08b)\n", toggled_num, toggled_num);
    return 0;
}