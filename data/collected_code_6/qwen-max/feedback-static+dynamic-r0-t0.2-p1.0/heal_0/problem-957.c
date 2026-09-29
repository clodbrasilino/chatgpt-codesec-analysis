#include <stdio.h>
#include <stdint.h>

int get_rightmost_set_bit_position(uint32_t num) {
    int position = 0;
    while (num > 0 && (num & 1) == 0) {
        num >>= 1;
        position++;
    }
    return position;
}

int main() {
    uint32_t num = 0x00000018; // Example number, binary: 00011000
    int position = get_rightmost_set_bit_position(num);
    printf("Position of rightmost set bit: %d\n", position);
    return 0;
}