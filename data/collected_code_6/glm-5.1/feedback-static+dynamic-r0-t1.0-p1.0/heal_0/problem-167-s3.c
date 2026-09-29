#include <stdio.h>
#include <limits.h>

unsigned int next_power_of_2(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    if ((n & (n - 1)) == 0) {
        return n;
    }
    if (n > UINT_MAX / 2) {
        return 0;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

int main(void) {
    unsigned int val;
    if (scanf("%u", &val) == 1) {
        unsigned int res = next_power_of_2(val);
        if (res == 0) {
            printf("Overflow\n");
        } else {
            printf("%u\n", res);
        }
    }
    return 0;
}