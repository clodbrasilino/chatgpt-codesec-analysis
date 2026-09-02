#include <stdio.h>

unsigned int setOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main(void) {
    unsigned int input = 0;
    unsigned int result = 0;

    printf("Enter a number: ");
    if (scanf("%u", &input) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    result = setOddBits(input);
    printf("Result after setting odd bits: %u\n", result);

    return 0;
}