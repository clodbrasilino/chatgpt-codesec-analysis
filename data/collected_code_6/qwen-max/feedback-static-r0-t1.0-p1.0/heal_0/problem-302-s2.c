#include <stdio.h>
#include <stdint.h>

int find_msb_set(uint32_t num) {
    int msb = -1;
    for (int i = 31; i >= 0; --i) {
        if ((num & (1u << i)) != 0) {
            msb = i;
            break;
        }
    }
    return msb;
}

int main() {
    uint32_t num = 0xabcdef01;
    int msb = find_msb_set(num);
    if (msb != -1) {
        printf("The most significant set bit is at position: %d\n", msb);
    } else {
        printf("No set bits found.\n");
    }
    return 0;
}