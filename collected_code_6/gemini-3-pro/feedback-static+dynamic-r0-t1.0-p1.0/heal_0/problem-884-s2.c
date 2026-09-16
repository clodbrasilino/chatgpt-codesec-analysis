#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool check_bits_in_range(uint32_t num, uint32_t L, uint32_t R);

bool check_bits_in_range(uint32_t num, uint32_t L, uint32_t R) {
    if (L > R || R > 31) {
        return false;
    }

    uint32_t mask = 0;
    
    if (R - L + 1 == 32) {
        mask = 0xFFFFFFFF;
    } else {
        mask = ((1U << (R - L + 1)) - 1) << L;
    }

    return (num & ~mask) == 0;
}

int main(void) {
    uint32_t num1 = 14; 
    uint32_t L1 = 1;
    uint32_t R1 = 3;

    if (check_bits_in_range(num1, L1, R1)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    uint32_t num2 = 17; 
    uint32_t L2 = 1;
    uint32_t R2 = 3;

    if (check_bits_in_range(num2, L2, R2)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}