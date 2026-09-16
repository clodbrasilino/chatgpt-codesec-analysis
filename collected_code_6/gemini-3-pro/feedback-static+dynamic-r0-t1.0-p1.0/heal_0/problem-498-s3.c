#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    unsigned int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    unsigned int num1 = 48;
    unsigned int num2 = 18;
    unsigned int result;

    if (num1 == 0 && num2 == 0) {
        return EXIT_FAILURE;
    }

    result = gcd(num1, num2);

    printf("GCD of %u and %u is %u\n", num1, num2, result);

    return EXIT_SUCCESS;
}