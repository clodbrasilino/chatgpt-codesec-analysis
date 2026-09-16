#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0xAAAAAAAA;
}

int main(void) {
    uint32_t num = 0;
    uint32_t result = 0;
    int scan_result = 0;

    scan_result = scanf("%u", &num);
    if (scan_result != 1) {
        return EXIT_FAILURE;
    }

    result = toggle_even_bits(num);
    
    printf("%u\n", result);

    return EXIT_SUCCESS;
}