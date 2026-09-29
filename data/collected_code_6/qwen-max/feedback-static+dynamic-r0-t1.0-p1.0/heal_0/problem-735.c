#include <stdio.h>
#include <stdint.h>

uint32_t toggle_middle_bits(uint32_t num) {
    uint32_t len = 0;
    uint32_t n = num;
    while (n > 0) {
        len++;
        n >>= 1;
    }
    if (len <= 2) {
        return num;
    }
    uint32_t mask = (1 << (len - 2)) - 1;
    return num ^ mask;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    num = toggle_middle_bits(num);
    printf("%u\n", num);
    return 0;
}