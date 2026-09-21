#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_even_bits(uint32_t num) {
    uint32_t mask = 0x55555555;
    return num | mask;
}

int main(void) {
    uint32_t input = 0;
    if (scanf("%" SCNu32, &input) == 1) {
        uint32_t result = set_even_bits(input);
        printf("%" PRIu32 "\n", result);
    } else {
        return 1;
    }
    return 0;
}