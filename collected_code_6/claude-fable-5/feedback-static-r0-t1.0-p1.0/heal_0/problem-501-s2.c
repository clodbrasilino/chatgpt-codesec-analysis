#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0U) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void)
{
    long first = 0L;
    long second = 0L;
    int result = 0;

    printf("Enter two positive integers: ");

    result = scanf("%ld %ld", &first, &second);
    if (result != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if ((first <= 0L) || (second <= 0L)) {
        fprintf(stderr, "Error: both numbers must be positive.\n");
        return EXIT_FAILURE;
    }

    if ((first > (long)UINT_MAX) || (second > (long)UINT_MAX)) {
        fprintf(stderr, "Error: input values are too large.\n");
        return EXIT_FAILURE;
    }

    printf("The greatest common divisor of %ld and %ld is %u\n",
           first, second, gcd((unsigned int)first, (unsigned int)second));

    return EXIT_SUCCESS;
}