#include <stdio.h>
#include <stdint.h>

uint32_t toggleBits(uint32_t num) {
    if(num == 0)
        return 0;
    uint32_t toggle_mask = ~((uint32_t)1u << (sizeof(num) * 8 - 1)) >> 1;
    toggle_mask <<= 1;
    return (num ^ toggle_mask);
}

int main(void) {
    uint32_t num = 2730;
    printf("%u\n", num);
    num = toggleBits(num);
    printf("%u\n", num);
    return 0;
}