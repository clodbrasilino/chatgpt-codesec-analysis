#include <stdio.h>
#include <stdint.h>

int most_significant_set_bit(uint32_t value) {
    if (value == 0) {
        return -1;
    }

    int bit_position = 0;

    while (value >>= 1) {
        bit_position++;
    }

    return bit_position;
}

int main(void) {
    uint32_t test_values[] = {0, 1, 2, 3, 4, 7, 8, 15, 16, 255, 1024, 0x80000000, 0xFFFFFFFF};
    size_t test_count = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < test_count; i++) {
        int result = most_significant_set_bit(test_values[i]);
        if (result == -1) {
            printf("Value: 0x%08X, MSB set bit: none\n", test_values[i]);
        } else {
            printf("Value: 0x%08X, MSB set bit: %d\n", test_values[i], result);
        }
    }

    return 0;
}