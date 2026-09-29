#include <stdio.h>
#include <stdint.h>

uint32_t toggle_even_bits(uint32_t num) {
    uint32_t mask = 0x55555555;
    return num ^ mask;
}

int main(void) {
    uint32_t input;
    if (scanf("%u", &input) != 1) {
        return 1;
    }
    uint32_t result = toggle_even_bits(input);
    printf("%u\n", result);
    return 0;
}