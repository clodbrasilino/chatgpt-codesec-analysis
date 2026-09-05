#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int find_msb_set(uint32_t num) {
    if (num == 0) {
        return -1;
    }
    int msb = 0;
    while (num >>= 1) {
        msb++;
    }
    return msb;
}

int main(void) {
    uint32_t values[] = {0, 1, 2, 16, 255, UINT32_MAX};
    size_t count = sizeof(values) / sizeof(values[0]);
    for (size_t i = 0; i < count; i++) {
        int res = find_msb_set(values[i]);
        if (res == -1) {
            printf("Input: %u, No set bits found.\n", values[i]);
        } else {
            printf("Input: %u, MSB set at position: %d\n", values[i], res);
        }
    }
    return 0;
}