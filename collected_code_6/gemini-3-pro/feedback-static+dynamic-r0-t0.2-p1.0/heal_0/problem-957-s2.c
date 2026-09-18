#include <stdio.h>

unsigned int get_rightmost_set_bit_position(unsigned int n) {
    unsigned int pos = 1;

    if (n == 0) {
        return 0;
    }

    while ((n & 1) == 0) {
        n >>= 1;
        pos++;
    }

    return pos;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 12, 18, 256};
    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_values; i++) {
        unsigned int pos = get_rightmost_set_bit_position(test_values[i]);
        printf("%u\n", pos);
    }

    return 0;
}