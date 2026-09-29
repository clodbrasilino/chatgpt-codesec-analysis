#include <stdio.h>
#include <math.h>

int has_even_divisor_count(unsigned long long n)
{
    unsigned long long root;

    if (n == 0ULL) {
        return -1;
    }

    root = (unsigned long long)sqrt((double)n);

    while (root * root > n) {
        root--;
    }
    while ((root + 1ULL) * (root + 1ULL) <= n) {
        root++;
    }

    if (root * root == n) {
        return 0;
    }

    return 1;
}

int main(void)
{
    unsigned long long number;
    int result;

    printf("Enter a positive integer: ");

    if (scanf("%llu", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (number == 0ULL) {
        fprintf(stderr, "Error: number must be greater than zero.\n");
        return 1;
    }

    result = has_even_divisor_count(number);

    if (result < 0) {
        fprintf(stderr, "Error: computation failed.\n");
        return 1;
    }

    if (result == 1) {
        printf("The count of divisors of %llu is even.\n", number);
    } else {
        printf("The count of divisors of %llu is odd.\n", number);
    }

    return 0;
}