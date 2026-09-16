#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int find_msb_set(uint32_t num) {
    if (num == 0) {
        return -1;
    }

    int msb = 0;
    while (num > 1) {
        num >>= 1;
        msb++;
    }

    return msb;
}

int main(void) {
    uint32_t num = 0;
    
    if (scanf("%u", &num) != 1) {
        return 1;
    }

    int msb = find_msb_set(num);

    if (msb != -1) {
        printf("%d\n", msb);
    } else {
        printf("-1\n");
    }

    return 0;
}