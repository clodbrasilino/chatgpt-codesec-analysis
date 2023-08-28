#include <stdio.h>

unsigned int setLeftmostUnsetBit(unsigned int num) {
    unsigned int mask = 1;

    while (num & mask) {
        mask <<= 1;
    }

    return num | mask;
}

int main() {
    unsigned int num = 10;
    unsigned int result = setLeftmostUnsetBit(num);

    printf("Number before setting leftmost unset bit: %u\n", num);
    printf("Number after setting leftmost unset bit: %u\n", result);

    return 0;
}