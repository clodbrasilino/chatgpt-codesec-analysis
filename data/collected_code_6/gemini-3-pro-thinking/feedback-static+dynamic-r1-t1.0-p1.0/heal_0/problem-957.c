#include <stdio.h>
#include <stdlib.h>

unsigned int get_rightmost_set_bit_position(unsigned int n);

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 10, 16, 256, 4294967295U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        unsigned int n = test_values[i];
        unsigned int pos = get_rightmost_set_bit_position(n);
        
        if (printf("%u -> %u\n", n, pos) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

unsigned int get_rightmost_set_bit_position(unsigned int n) {
    unsigned int position = 1;

    if (n == 0) {
        return 0;
    }

    while ((n & 1U) == 0) {
        n >>= 1;
        position++;
    }

    return position;
}