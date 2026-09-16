#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t set_even_bits(uint32_t n) {
    return n | 0xAAAAAAAA;
}

int main(void) {
    uint32_t input;
    uint32_t result;
    int scan_res;

    scan_res = scanf("%u", &input);
    if (scan_res != 1) {
        return EXIT_FAILURE;
    }

    result = set_even_bits(input);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}