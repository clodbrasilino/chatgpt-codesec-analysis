#include <stdio.h>

unsigned int setEvenBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%u", &num);
    unsigned int result = setEvenBits(num);
    printf("Number with all even bits set: %u\n", result);
    return 0;
}