#include <stdio.h>
#include <stdint.h>

int all_bits_in_range(uint32_t value, unsigned int high, unsigned int low) {
    if (low > high || high > 31) {
        return -1;
    }

    unsigned int num_bits = high - low + 1;
    uint32_t mask = ((num_bits >= 32) ? 0xFFFFFFFFu : ((1u << num_bits) - 1)) << low;

    return (value & ~mask) == 0;
}

int main(void) {
    uint32_t test_val = 0x1C;
    int result = all_bits_in_range(test_val, 4, 2);

    if (result == -1) {
        printf("Invalid range\n");
    } else if (result == 1) {
        printf("All bits are within the range\n");
    } else {
        printf("Bits outside the range\n");
    }

    return 0;
}