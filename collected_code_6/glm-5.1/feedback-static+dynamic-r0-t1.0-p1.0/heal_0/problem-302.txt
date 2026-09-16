#include <stdio.h>
#include <limits.h>

int find_msb_set_bit(unsigned int num) {
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
    unsigned int val = 0;
    if (scanf("%u", &val) == 1) {
        int res = find_msb_set_bit(val);
        if (res == -1) {
            printf("%d\n", res);
        } else {
            printf("%d\n", res);
        }
    }
    return 0;
}