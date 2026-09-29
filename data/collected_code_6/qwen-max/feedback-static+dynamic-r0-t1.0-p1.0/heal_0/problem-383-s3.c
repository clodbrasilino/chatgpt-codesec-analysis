#include <stdio.h>
#include <stdint.h>

uint32_t toggle_odd_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main() {
    uint32_t num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        return 1;
    }
    uint32_t result = toggle_odd_bits(num);
    printf("Result: %u\n", result);
    return 0;
}