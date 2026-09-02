#include <stdio.h>
#include <stdint.h>

int get_rightmost_set_bit_position(uint32_t num) {
    int position = 0;
    if (num == 0) return -1;
    while ((num & 1) == 0) {
        num >>= 1;
        position++;
    }
    return position;
}

int main() {
    uint32_t num = 0x00000018; // Example number
    int position = get_rightmost_set_bit_position(num);
    if (position != -1) {
        printf("The position of the rightmost set bit is: %d\n", position);
    } else {
        printf("No set bits found.\n");
    }
    return 0;
}