#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int has_even_divisor_count(unsigned long n);

int has_even_divisor_count(unsigned long n)
{
    unsigned long root;

    if (n == 0UL) {
        return -1;
    }

    root = (unsigned long)sqrt((double)n);

    while (root * root > n) {
        root--;
    }
    while ((root + 1UL) * (root + 1UL) <= n) {
        root++;
    }

    if (root * root == n) {
        return 0;
    }

    return 1;
}

int main(void)
{
    unsigned long number = 0UL;
    int result;

    printf("Enter a positive integer: ");

    if (scanf("%lu", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = has_even_divisor_count(number);

    if (result == -1) {
        fprintf(stderr, "Error: number must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("The count of divisors of %lu is even.\n", number);
    } else {
        printf("The count of divisors of %lu is odd.\n", number);
    }

    return EXIT_SUCCESS;
}