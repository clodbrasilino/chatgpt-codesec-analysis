#include <stdio.h>

unsigned int toggleOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    unsigned int input = 0;
    printf("Enter a number: ");
    if (scanf("%u", &input) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    unsigned int result = toggleOddBits(input);
    printf("Result: %u\n", result);

    return 0;
}