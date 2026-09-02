#include <stdio.h>
#include <stdint.h>

int get_rightmost_set_bit(uint32_t n) {
    return (n & -n);
}

int main() {
    uint32_t num = 0x5A; // Example number
    int result = get_rightmost_set_bit(num);
    printf("Rightmost set bit: %d\n", result);
    return 0;
}