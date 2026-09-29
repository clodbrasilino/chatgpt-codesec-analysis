#include <stdio.h>
#include <stdint.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0x55555555;
}

int main() {
    uint32_t input = 0;
    if (scanf("%u", &input) == 1) {
        uint32_t result = toggle_even_bits(input);
        printf("%u\n", result);
        return 0;
    }
    return 1;
}