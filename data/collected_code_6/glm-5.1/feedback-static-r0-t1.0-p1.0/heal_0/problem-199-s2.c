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
    return n - (n >> 1);
}

int main(void) {
    unsigned int num;
    if (scanf("%u", &num) != 1) {
        return 1;
    }
    unsigned int result = highest_power_of_2(num);
    printf("%u\n", result);
    return 0;
}