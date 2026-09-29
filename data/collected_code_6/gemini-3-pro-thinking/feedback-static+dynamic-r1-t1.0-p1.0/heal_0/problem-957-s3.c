#include <stdio.h>
#include <stdlib.h>

unsigned int get_rightmost_set_bit_position(unsigned int n);

unsigned int get_rightmost_set_bit_position(unsigned int n) {
    unsigned int position = 1;

    if (n == 0) {
        return 0;
    }

    while ((n & 1) == 0) {
        n >>= 1;
        position++;
    }

    return position;
}

int main(void) {
    unsigned int test_values[] = {18, 0, 1, 32, 128, 255};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    unsigned int pos;

    for (i = 0; i < num_tests; i++) {
        pos = get_rightmost_set_bit_position(test_values[i]);
        if (printf("%u\n", pos) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}