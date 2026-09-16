#include <stdio.h>
#include <stdint.h>

int are_bits_unset(uint32_t n, int start, int end) {
    uint32_t mask = ((1U << (end - start + 1)) - 1) << start;
    return (n & mask) == 0;
}

int main() {
    uint32_t num = 0b1010101010101010;
    int start = 4;
    int end = 10;

    if (are_bits_unset(num, start, end)) {
        printf("All bits in the range %d to %d are unset.\n", start, end);
    } else {
        printf("Not all bits in the range %d to %d are unset.\n", start, end);
    }

    return 0;
}