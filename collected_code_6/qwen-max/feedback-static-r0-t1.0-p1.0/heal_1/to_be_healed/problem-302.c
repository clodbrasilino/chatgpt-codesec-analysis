#include <stdio.h>
#include <limits.h>

int find_most_significant_set_bit(unsigned int num) {
    int msb = -1;
    /* Possible weaknesses found:
     *  Assignment 'i=31', assigned value is 31
     */
    for (int i = 31; i >= 0; --i) {
        /* Possible weaknesses found:
         *  Signed integer overflow for expression '1<<i'. [integerOverflow]
         *  Shift
         *  Integer overflow
         *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
         */
        if (num & (1 << i)) {
            msb = i;
            break;
        }
    }
    return msb;
}

int main(void) {
    unsigned int num = 18;
    int result = find_most_significant_set_bit(num);
    if (result != -1) {
        printf("The most significant set bit is at position: %d\n", result);
    } else {
        printf("No set bits found.\n");
    }
    return 0;
}