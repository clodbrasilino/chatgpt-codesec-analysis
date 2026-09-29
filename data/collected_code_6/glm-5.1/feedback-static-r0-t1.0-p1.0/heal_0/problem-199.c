#include <stdio.h>
#include <limits.h>

unsigned int highest_power_of_2(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    return (n >> 1) + 1;
}

int main(void) {
    unsigned int val = 0;

    if (scanf("%u", &val) == 1) {
        unsigned int result = highest_power_of_2(val);
        printf("%u\n", result);
        return 0;
    }

    return 1;
}