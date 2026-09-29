#include <stdio.h>

unsigned int setEvenBits(unsigned int num) {
    return num | 0xAAAAAAAA;
}

int main() {
    unsigned int num = 23;
    printf("Number with even bits set: %u", setEvenBits(num));
    return 0;
}