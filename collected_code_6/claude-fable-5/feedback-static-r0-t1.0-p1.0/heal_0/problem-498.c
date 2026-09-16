#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b);

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0U) {
        unsigned int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(void)
{
    unsigned int x = 0U;
    unsigned int y = 0U;

    printf("Enter two positive integers: ");

    if (scanf("%u %u", &x, &y) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if ((x == 0U) || (y == 0U)) {
        fprintf(stderr, "Error: integers must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("GCD of %u and %u is %u\n", x, y, gcd(x, y));

    return EXIT_SUCCESS;
}