#include <stdio.h>
#include <stdint.h>

uint32_t set_rightmost_unset_bit(uint32_t n);

uint32_t set_rightmost_unset_bit(uint32_t n) {
    return n | (n + 1);
}

int main(void) {
    uint32_t test_value = 21;
    uint32_t result;

    result = set_rightmost_unset_bit(test_value);

    if (printf("%u\n", result) < 0) {
        return 1;
    }

    return 0;
}