#include <stdio.h>
#include <stdlib.h>

unsigned long long min_operations(long long a, long long b)
{
    unsigned long long result;

    if (a >= b) {
        result = (unsigned long long)a - (unsigned long long)b;
    } else {
        result = (unsigned long long)b - (unsigned long long)a;
    }

    return result;
}

int main(void)
{
    long long a;
    long long b;
    unsigned long long ops;

    printf("Enter first number: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Error: invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%lld", &b) != 1) {
        fprintf(stderr, "Error: invalid input for second number\n");
        return EXIT_FAILURE;
    }

    ops = min_operations(a, b);

    if (printf("Minimum operations required: %llu\n", ops) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}