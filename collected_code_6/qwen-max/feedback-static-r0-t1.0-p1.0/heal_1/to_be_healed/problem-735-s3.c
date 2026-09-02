#include <stdio.h>
#include <stdint.h>

uint32_t toggle_bits_except_first_last(uint32_t num) {
    uint32_t first_bit = num & 1;
    /* Possible weaknesses found:
     *  Signed integer overflow for expression '1<<31'. [integerOverflow]
     *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
     */
    uint32_t last_bit = (num & (1 << 31)) >> 31;
    uint32_t middle_bits = (num >> 1) & ~(1u << 30);
    middle_bits = ~middle_bits & 0x7FFFFFFE;
    return (last_bit << 31) | (middle_bits << 1) | first_bit;
}

int main() {
    uint32_t num = 0b11010101010101010101010101010101;
    uint32_t result = toggle_bits_except_first_last(num);

    printf("Original number: %u\n", num);
    printf("Toggled number: %u\n", result);

    return 0;
}