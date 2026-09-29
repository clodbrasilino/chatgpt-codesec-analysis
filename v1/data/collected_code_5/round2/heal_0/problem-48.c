#include <stdio.h>

unsigned int setOddBits(unsigned int num) {
    unsigned int i;
    for (i = 1; i < sizeof(num) * 8; i += 2) {
        num |= 1 << i;
    }
    return num;
}

int main(){
    unsigned int num = 10;
    printf("Original number: %d\n", num);
    num = setOddBits(num);
    printf("Number after setting odd bits: %d\n", num);
    return 0;
}