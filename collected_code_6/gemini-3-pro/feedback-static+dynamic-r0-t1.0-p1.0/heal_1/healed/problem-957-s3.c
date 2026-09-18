#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(unsigned int n);

int get_rightmost_set_bit_position(unsigned int n) {
    int position = 1;

    if (n == 0) {
        return 0;
    }

    while ((n & 1U) == 0) {
        n >>= 1;
        position++;
    }

    return position;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 12, 18, 20};
    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_values; i++) {
        int position = get_rightmost_set_bit_position(test_values[i]);
        if (printf("%d\n", position) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}