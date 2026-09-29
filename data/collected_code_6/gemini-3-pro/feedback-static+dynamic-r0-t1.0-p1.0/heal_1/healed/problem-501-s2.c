#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    unsigned int num1 = 0;
    unsigned int num2 = 0;
    unsigned int divisor = 0;

    if (scanf("%u %u", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    if (num1 == 0 && num2 == 0) {
        return EXIT_FAILURE;
    }

    divisor = gcd(num1, num2);
    
    printf("%u\n", divisor);

    return EXIT_SUCCESS;
}