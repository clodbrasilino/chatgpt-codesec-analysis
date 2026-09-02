#include <stdio.h>
#include <stdint.h>

uint32_t highest_power_of_two(uint32_t n) {
    uint32_t power = 0;
    while (n > 1) {
        n >>= 1;
        power++;
    }
    return 1u << power;
}

int main() {
    uint32_t n;
    printf("Enter a number: ");
    if (scanf("%u", &n) == 1) {
        uint32_t result = highest_power_of_two(n);
        printf("The highest power of 2 less than or equal to %u is: %u\n", n, result);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}