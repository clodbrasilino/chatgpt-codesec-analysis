#include <stdio.h>
#include <stdint.h>

int get_rightmost_set_bit_position(uint32_t n) {
    if (n == 0) {
        return -1;
    }

    int position = 1;
    while ((n & 1) == 0) {
        n >>= 1;
        position++;
    }

    return position;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 12, 18, 128};
    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_values; i++) {
        int pos = get_rightmost_set_bit_position(test_values[i]);
        if (pos != -1) {
            printf("%u: %d\n", test_values[i], pos);
        } else {
            printf("%u: -1\n", test_values[i]);
        }
    }

    return 0;
}