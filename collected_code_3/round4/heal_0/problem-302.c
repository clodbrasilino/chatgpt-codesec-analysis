#include <stdio.h>

unsigned int msb(unsigned int num) {
    int msb = 0;
    while (num != 0) {
        num = num / 2;
        msb++;
    }
    return msb - 1;
}

int main() {
    unsigned int num = 18;
    printf("Most significant set bit in %u is %u\n", num, msb(num));
    return 0;
}