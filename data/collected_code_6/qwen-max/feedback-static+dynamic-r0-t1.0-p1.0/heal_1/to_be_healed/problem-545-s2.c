#include <stdio.h>
#include <stdint.h>

void toggle_first_last_bits(uint32_t *num) {
    uint32_t mask = 1 | (1u << (sizeof(uint32_t) * 8 - 1));
    *num ^= mask;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    /* Possible weaknesses found:
     *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'unsigned int'. [invalidPrintfArgType_uint]
     */
    printf("Original number in binary: %zu\n", num);
    toggle_first_last_bits(&num);
    /* Possible weaknesses found:
     *  %zu in format string (no. 1) requires 'size_t' but the argument type is 'unsigned int'. [invalidPrintfArgType_uint]
     */
    printf("Number after toggling first and last bits in binary: %zu\n", num);
    return 0;
}