#include <stdio.h>

unsigned int msbSetBit(unsigned int num) {
    if(num == 0)
        return 0;

    int msb = 0;
    while(num != 0) {
        num = num / 2;
        msb++;
    }
    return msb - 1;
}

int main() {
    unsigned int num = 10;
    printf("Most significant set bit in %u is %u\n", num, msbSetBit(num));
    return 0;
}