#include <stdio.h>
#include <stdint.h>

int differ_by_one_bit(uint32_t a, uint32_t b) {
    uint32_t diff = a ^ b;
    return diff != 0 && (diff & (diff - 1)) == 0;
}

int main(void) {
    uint32_t x = 12;
    uint32_t y = 8;
    
    if (differ_by_one_bit(x, y)) {
        printf("%u and %u differ at one bit position only\n", x, y);
    } else {
        printf("%u and %u do not differ at one bit position only\n", x, y);
    }
    
    return 0;
}