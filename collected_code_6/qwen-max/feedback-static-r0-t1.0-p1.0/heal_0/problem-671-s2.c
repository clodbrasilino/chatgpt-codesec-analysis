#include <stdio.h>
#include <stdint.h>

uint32_t set_right_most_unset_bit(uint32_t n) {
    return n | (n + 1);
}

int main() {
    uint32_t num = 0b1010;
    uint32_t result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);
    return 0;
}