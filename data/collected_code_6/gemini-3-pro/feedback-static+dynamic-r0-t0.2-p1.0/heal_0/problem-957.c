#include <stdio.h>

unsigned int get_rightmost_set_bit_position(unsigned int n);

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
    unsigned int test_values[] = {0, 1, 2, 12, 18, 64};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        unsigned int pos = get_rightmost_set_bit_position(test_values[i]);
        if (pos == 0) {
            printf("0\n");
        } else {
            printf("%u\n", pos);
        }
    }

    return 0;
}